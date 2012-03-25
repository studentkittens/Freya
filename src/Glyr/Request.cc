#include "Request.hh"
#include "../Log/Writer.hh"
#include "../Init/Path.hh"

namespace Glyr
{
    Stack::Stack() :
        pool(4,false),
        jobCounter(0),
        gotDestroyed(false),
        dbConnection(NULL)
    {
        glyr_init();
        atexit(glyr_cleanup);

        /* 
         * Find out path and create DB
         */
        Init::Path cfgpath;
        Debug("Writing metadata.db to: %s",cfgpath.path_to_metadata_db().c_str());

        dbConnection = glyr_db_init(cfgpath.get_config_dir().c_str());
        if(dbConnection == NULL)
        {
            Warning("Unable to write metadata.db for unknown reason.");
        }
    }

    ////////////////////////

    void Stack::destroy()
    {
        Info("Shutting down Metadatasystem...");
        gotDestroyed = true;
        pool.shutdown(true);

        /*
         * Send a goodbye to every Query, so they exit early 
         */
        for(auto it = murderList.begin(); it != murderList.end(); it++) {
            glyr_signal_exit(*it);
        }

        /*
         * Wait till all jobs finished..
         */
        condMutex.lock();
        while(jobCounter != 0) {
            destroyCond.wait(condMutex);
        }
        condMutex.unlock();

        /*
         * Kill the DB connection
         */
        glyr_db_destroy(dbConnection);

    }

    ////////////////////////

    void Stack::thread(GlyrQuery * q, UpdateInterface * intf, Glib::Dispatcher * disp, int reqID)
    {
        jobCounter++;

        GLYR_ERROR err;
        GlyrMemCache * results = NULL;
        results = glyr_get(q,&err,NULL);
                
        /*
         * Make sure only on deliver callback 
         * is served at a time, the actual
         * callback is called inside the mainthread
         * (thanks to the dispatcher)
         *
         * Only deliver when request is the last one send.
         */
        if(intf != NULL) {
            if(intf->requestCounter == reqID) {
                Glib::Mutex::Lock lock(deliverMutex);
                disp->connect(sigc::bind(
                              sigc::mem_fun(intf,&UpdateInterface::deliver_internal),results,disp,true)
                             );

                disp->emit();
            } else {
                /* 
                 * Glib::Dispatcher does not like to be freed
                 * in another thread in which it had been instanced,
                 * so use it to kill itself.. 
                 */
                disp->connect(sigc::bind(
                              sigc::mem_fun(intf,&UpdateInterface::deliver_internal),results,disp,false)
                             );

                disp->emit();
                glyr_free_list(results);
            }
        }

        /*
         * Now remove the Query from the murderlist
         */
        {
            Glib::Mutex::Lock lock(deleteMutex);
            for(QueryList::iterator it = murderList.begin(); it != murderList.end(); it++)
            {
                GlyrQuery * ptr = *it;
                if(ptr == q)
                {
                    murderList.erase(it);
                    glyr_query_destroy(q);
                    g_slice_free(GlyrQuery,q);
                    q = NULL;
                    break;
                }
            }
        }

        /*
         * Notify eventually listening destroy() func
         */
        {
            Glib::Mutex::Lock lock(condMutex);
            jobCounter--;
            destroyCond.signal();
        }
    }

    ////////////////////////
    ////     PUBLIC    /////
    ////////////////////////

    void Stack::enqueue(UpdateInterface * intf)
    {
        intf->queueCounter++;
    }

    ////////////////////////

    void Stack::request(UpdateInterface * intf, MPD::Song& song, GLYR_GET_TYPE type, int number)
    {
        request(intf,
                song.get_tag(MPD_TAG_ARTIST),
                song.get_tag(MPD_TAG_ALBUM ),
                song.get_tag(MPD_TAG_TITLE ),
                type,number);
    }

    ////////////////////////

    void Stack::request(UpdateInterface * intf, const char * artist, const char * album, const char * title, GLYR_GET_TYPE type, int number)
    {
        if(gotDestroyed == false) 
        {
            GlyrQuery * query = (GlyrQuery*)g_slice_alloc(sizeof(GlyrQuery));
            if(query != NULL) 
            {
                /* 
                 * Set up a suitable query. 
                 * Also see: http://sahib.github.com/glyr/doc/html/libglyr-Glyr.html
                 */ 
                glyr_query_init(query);
                glyr_opt_type(query,type);
                glyr_opt_artist(query,(char*)artist);
                glyr_opt_album (query,(char*)album );
                glyr_opt_title (query,(char*)title );
                glyr_opt_parallel(query,1);
                glyr_opt_number(query,number);
                glyr_opt_lookup_db(query,dbConnection);

                if(LogGetVerbosity == Log::LOG_DEBUG) {
                    glyr_opt_verbosity(query,2);
                }

                /* 
                 * Dispatcher needs to be instanced in
                 * the thread of the mainloop, i.e. here
                 */
                auto * disp = new Glib::Dispatcher; 

                /* 
                 * The request counter only gets incremented if
                 * no requests are enqueued (-> delivered as one)
                 */
                {
                    Glib::Mutex::Lock lock(addMutex);
                    if(intf->queueCounter)
                        --(intf->queueCounter);
                    else
                        ++(intf->requestCounter);
                }

                murderList.push_back(query);
                pool.push(sigc::bind(
                            sigc::mem_fun(*this,&Stack::thread),query,intf,disp,intf->requestCounter)
                         );
            }
        }
    }
}
