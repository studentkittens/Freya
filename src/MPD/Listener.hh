#ifndef FREYA_LISTENER_GUARD
#define FREYA_LISTENER_GUARD

#include "../includes.hh"
#include "Status.hh"
#include "NotifyData.hh"
#include "Connection.hh"

/* Typedef, so no error-prone rewriting of this sig */
typedef sigc::signal<void,enum mpd_idle, MPD::NotifyData&> EventNotifier;

namespace MPD
{
    class Listener
    {
        public:
            Listener(EventNotifier * notifier, Connection& sync_conn);
            ~Listener();

            /* Enter idle mode
             * Returns: true on success 
             */
            bool enter(void);

            /* Leave idle mode (in order to send commands)
            */
            void leave(void);

            /* Checks if connection is in idle mode
            */
            bool is_idling(void);

            //---------------//
            // Classmembers  //
            //---------------//

            NotifyData& get_notify_data(void);

        private:
        
            /**
             * Utility (therefore static) function to
             * convert a GIOCondition bit mask to #mpd_async_event.
             */
            static enum mpd_async_event GIOCondition_to_MPDAsyncEvent(Glib::IOCondition condition);

            //--------------------------------

            /**
             * Converts a #mpd_async_event bit mask to GIOCondition.
             */
            static Glib::IOCondition MPDAsyncEvent_to_GIOCondition(enum mpd_async_event events);


            /* check if async connection is doing weird things */
            bool check_async_error(void);
            bool recv_parseable(void);
            gboolean io_callback(Glib::IOCondition condition);
            bool parse_response(char *line);
            void invoke_user_callback(void);
            void create_watch(enum mpd_async_event events);

            //-----------------//
            // Instancemembers //
            //-----------------//

            /* true if in idlemode */
            bool is_idle;

            /* A reponse parser */
            struct mpd_parser * mp_Parser;

            /* Non blocking connection */
            struct mpd_async  * async_conn;

            /* The fd id of async_conn */
            int async_socket_fd;

            /* What IO events did happen? */
            enum mpd_async_event io_eventmask;

            /* The actual events (like "player","mixer".. etc) */
            unsigned idle_events;

            /* A functor representing the io_callback */
            sigc::connection io_functor;

            /* emit() is called on this on events */
            EventNotifier * mp_Notifier;

            /* MPD Status */
            Status * mp_Status;

            /* Synchronous connection */
            Connection * mp_Conn;

            /* The data passed to the observer */
            NotifyData m_NData;
    };
}
#endif
