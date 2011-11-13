#ifndef FREYA_CLIENT
#define FREYA_CLIENT 

#include "../includes.hh"
#include  "Connection.hh"
#include  "Listener.hh"

namespace MPD
{
    class Client
    {
        public:

            Client();
            ~Client();

            void connect(void);
            void disconnect(void);

            /* Go to next song */
            bool send_command(const char * command);

            /* List contents of current playlist */
            void list_queue(void);

            /* Playback */
            bool playback_next(void);
            bool playback_prev(void);
            bool playback_stop(void);
            bool playback_play(void);
            bool playback_pause(void);

            /**
             * @brief Get the notify sigc::signal
             *
             * Use connect() on it. This is called always once a new event
             * happens. See the typedef in Listener.hh for the exact signature
             *
             * @return the sigc::signal 
             */
            EventNotifier& get_notify(void);

        private:

            /**
             * @brief 
             */
            void go_idle(void);
            /**
             * @brief 
             */
            void go_busy(void);

            gboolean timeout_reconnect(void);
            bool check_error(void);
            void handle_errors(enum mpd_error err);

            // Instancevars //

            /* The wrapped up mpd_connection */
            Connection conn;

            /* The event notifier */
            Listener * listener;

            /* The slot which observers can connect to */
            EventNotifier m_Notifier;
    };

}

#endif
