#ifndef FREYA_GLYR_REQUEST_HH
#define FREYA_GLYR_REQUEST_HH

#include "../MPD/Client.hh"
#include "../Utils/Singleton.hh"
#include "UpdateInterface.hh"
#include <gdkmm/pixbuf.h>

#include <glyr/cache.h>

namespace Glyr 
{
    /**
     * @brief Glyr related Util function to turn a GlyrMemCache to an pixbuf
     *
     * @param c the cache, must be imagedata.
     * @param size_x width
     * @param size_y height
     * @param aspect keep aspect?
     *
     * @return a newly Refpointerd Pixbuf
     */
    Glib::RefPtr<Gdk::Pixbuf> create_pixbuf_from_cache(GlyrMemCache * c, int size_x = 150, int size_y = 150, bool aspect = false);

    /////////////////////////////

    class Stack
    {
        DEF_SINGLETON(Stack)

        public:

            /**
             * @brief Requets online metadata
             *
             * @param song A song with tagged artist/album/title
             * @param type one of the GLYR_GET_TYPE enum
             * @param number number of items, by default just one
             */
            void request(UpdateInterface * intf, MPD::Song& song, GLYR_GET_TYPE type, int number = 1);
            /**
             * @brief Requets online metadata
             *
             * @param artist Artist (will be sanitized)
             * @param album Album (will be sanitized)
             * @param title Title (will be sanitized)
             * @param type one of the GLYR_GET_TYPE enum
             * @param number number of items, by default just one
             */
            void request(UpdateInterface * intf,const char * artist, const char *  album, const char * title, GLYR_GET_TYPE type, int number = 1);

            /*
             * @brief Deinitializes glyr, kills all running queries, closes db
             */
            void destroy();

            /**
             * @brief Begin a request
             *
             * This is not necessary to call - most of the time it's just
             * fine to call request(), but if you want to group several 
             * requests in one response use begin_request() and end_request()
             * to wrap your requests, so they get delievered as "one", 
             * otherwise only the most recent request gets delivered 
             */
            void enqueue(UpdateInterface * intf);

        private:

            /*
             * Actual thread function that calls
             * glyr_get() and notifies the client
             */
            void thread(GlyrQuery * q, UpdateInterface * intf, Glib::Dispatcher * disp, int reqID);

            // Vars

            /*
             * A list of Queries that are running currently,
             * this is currently used to call glyr_signal_exit()
             * at program termination
             */
            typedef std::vector<GlyrQuery*> QueryList;
            QueryList murderList;

            /*
             * A pool of parallel executing Queries,
             * each thread one request
             */
            Glib::ThreadPool pool;

            /* 
             * A counter of currently running jobs,
             * once could also just use murderList.size(),
             * which is not atomar and would require 
             * additional locking
             */
            int jobCounter;

            /*
             * Locking stuff.
             */
            Glib::Cond destroyCond;
            Glib::Mutex deliverMutex, condMutex, deleteMutex;

            /*
             * True once destroy() was called
             */
            bool gotDestroyed;

            /*
             * Database connection
             */
            GlyrDatabase * dbConnection;
    };
}

#endif /* end of include guard: FREYA_GLYR_REQUEST_HH */
