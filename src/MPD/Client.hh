 /***********************************************************
* This file is part of Freya 
* - A free MPD Gtk3 MPD Client -
* 
* Authors: Christopher Pahl, Christoph Piechula,
*          Eduard Schneider, Marc Tigges
*
* Copyright (C) [2011-2012]
* Hosted at: https://github.com/studentkittens/Freya
*
*              __..--''``---....___   _..._    __
*    /// //_.-'    .-/";  `        ``<._  ``.''_ `. / // /
*   ///_.-' _..--.'_                        `( ) ) // //
*   / (_..-' // (< _     ;_..__               ; `' / ///
*    / // // //  `-._,_)' // / ``--...____..-' /// / //  
*  Ascii-Art by Felix Lee <flee@cse.psu.edu>
*
* Freya is free software: you can redistribute it and/or modify
* it under the terms of the GNU General Public License as published by
* the Free Software Foundation, either version 3 of the License, or
* (at your option) any later version.
*
* Freya is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
* GNU General Public License for more details.
*
* You should have received a copy of the GNU General Public License
* along with Freya. If not, see <http://www.gnu.org/licenses/>.
**************************************************************/
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
    /**
     * @brief You can call connect on this.
     *
     * It gets emitted by the client whenever the connection changes,
     * i.e. when getting disconnected or connected, in former case 
     * 'false' is passed as argument, in the latter 'true'
     */
    typedef sigc::signal<void,bool> ConnectionNotifier;

    class Client
    {
        public:

            /**
             * @brief Instance the client
             *
             * If settings.connection.autoconnect is set to true
             * This also connects already anc calls force_update()
             */
            Client();

            /**
             * @brief Disconnects also.
             */
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

            /* TODO: This is more appropiate in MPD::Playlist.. */
            void playlist_remove(const char * name);
            void playlist_add(const char * name);
            void playlist_load(const char * name);
            void playlist_rename(const char * source, const char * dest);
            void playlist_save(const char * name);

            void queue_add(const char * url);
            void queue_clear(void);
            void queue_delete(unsigned pos);
            void queue_delete_range(unsigned pos_start, unsigned pos_end);

            unsigned database_update(const char * path);
            unsigned database_rescan(const char * path);
            
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

            /**
             * @brief Register for connection changes
             *
             * @return a sigc::signal, you can call connect() on
             */
            ConnectionNotifier& signal_connection_change(void);
            
            /* Commandlists */
            void begin(void);
            void commit(void);

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

            /* Client::begin() was called, 
             * but not yet commit */
            bool m_ListBegun;

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
