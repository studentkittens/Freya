#include "Request.hh"
#include "../Log/Writer.hh"

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
        dbConnection = glyr_db_init("/tmp/");
    }

    ////////////////////////

    void Stack::destroy()
    {
        Info("Shutting down Metadatasystem...");

        /*
         * Send a goodbye to every Query, so they exit early 
         */
        for(QueryList::iterator it = murderList.begin(); it != murderList.end(); it++) {
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
         * Clean up
         */
        gotDestroyed = true;
        glyr_db_destroy(dbConnection);
        pool.shutdown(true);

    }

    ////////////////////////

    void Stack::thread(GlyrQuery * q, UpdateInterface * intf, Glib::Dispatcher * disp)
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
         */
        if(intf != NULL) {
            Glib::Mutex::Lock lock(deliverMutex);

            disp->connect(sigc::bind(sigc::mem_fun(intf,&UpdateInterface::deliver_internal),results,disp));
            disp->emit();
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
        condMutex.lock();
        jobCounter--;
        destroyCond.signal();
        condMutex.unlock();
    }

    ////////////////////////

    void Stack::request(UpdateInterface * intf, MPD::Song& song, GLYR_GET_TYPE type, int number)
    {
        request(intf,
                song.get_tag(MPD_TAG_ARTIST,0),
                song.get_tag(MPD_TAG_ALBUM, 0),
                song.get_tag(MPD_TAG_TITLE, 0),
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

                Glib::Dispatcher * disp = new Glib::Dispatcher;

                murderList.push_back(query);
                pool.push(sigc::bind(sigc::mem_fun(*this,&Stack::thread),query,intf,disp));
            }
        }
    }
}
