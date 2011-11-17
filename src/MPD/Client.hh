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

            void toggle_random(void);
            void toggle_consume(void);
            void toggle_repeat(void);
            void toggle_single(void);

            /**
             * @brief set the volume
             * 
             * @param vol Must be in [0-100]
             */
            void set_volume(unsigned vol);
            unsigned get_volume(void);
            /**
             * @brief Get the current MPD::Status
             *
             * @return A reference to it. Do not modify.
             */
            Status * get_status(void);

            // TODO: might get removed, and fetched from the MPD::Queue instead
            Song get_song_at_id(unsigned id);

            /**
             * @brief Get the notify sigc::signal
             *
             * Use connect() on it. This is called always once a ne, ...w event
             * happens. See the typedef in Listener.hh for the exact signature
             *, ...
             * @return the sigc::signal
             */
            EventNotifier& get_notify(void);

            void force_update(void);

        private:

            void go_idle(void);
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
