#ifndef FREYA_CLIENT_GUARD
#define FREYA_CLIENT_GUARD

#include "../includes.hh"
#include  "Connection.hh"
#include  "Listener.hh"

/* Songlist interface */
#include "../AbstractItemlist.hh"
#include "../AbstractFilebrowser.hh"


namespace MPD
{
    typedef sigc::signal<void,bool> ConnectionNotifier;

    class Client
    {
        public:

            Client();
            ~Client();

            void connect(void);
            void disconnect(void);
            bool is_connected(void);

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

            void play_song_at_id(unsigned song_id);           
 
            void playback_seek(unsigned song_id, unsigned abs_time);

            /**
             * @brief set the volume
             * 
             * @param vol Must be in [0-100]
             */
            void set_volume(unsigned vol);

            /**
             * @brief Get the current MPD::Status
             *
             * @return A reference to it. Do not modify.
             */
            Status * get_status(void);

            /**
             * @brief Get the notify sigc::signal
             *
             * Use connect() on it. This is called always once a ne, ...w event
             * happens. See the typedef in Listener.hh for the exact signature
             *, ...
             * @return the sigc::signal
             */
            EventNotifier& get_notify(void);


            

            ConnectionNotifier& signal_connection_change(void);

            /**
             * @brief Forces client update
             *
             * Updates status, stats, current song 
             * and sends all possible events to all connected listeners
             *
             */
            void force_update(void);

            /**
             * @brief Fetches the playlist from the mpd server
             *
             * @param data_model A user defined class, that inherits from AbstractSonglist 
             *
             * @return the number of filled items.
             */
            void fill_queue(AbstractItemlist& data_model);
            void fill_playlists(AbstractItemlist& data_model);
            void fill_filelist(AbstractFilebrowser& data_model, const char * path);

        private:

            void go_idle(void);
            void go_busy(void);

            gboolean timeout_reconnect(void);
            bool check_error(void);
            void handle_errors(enum mpd_error err);

            /* Instancevars */

            /* The wrapped up mpd_connection */
            Connection m_Conn;

            /* The event notifier */
            Listener * listener;

            /* The slot which observers can connect to */
            EventNotifier m_Notifier;

            /* Inform observers if connection changes happened */
            ConnectionNotifier m_ConnNotifer;
    };

}

#endif
