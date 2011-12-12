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

#include  "BaseClient.hh"

/* Songlist interface */
#include "../AbstractItemlist.hh"
#include "../AbstractFilebrowser.hh"

namespace MPD
{
    class Client : public BaseClient
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

            /* Playback */
            bool playback_next(void);
            bool playback_prev(void);
            bool playback_stop(void);
            bool playback_play(void);
            bool playback_pause(void);
            
            void playback_seek(unsigned song_id, unsigned abs_time);
            void playback_crossfade(unsigned seconds);

            void toggle_random(void);
            void toggle_consume(void);
            void toggle_repeat(void);
            void toggle_single(void);

            void play_song_at_id(unsigned song_id);           

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
             * @brief Fetches the playlist from the mpd server
             *
             * @param data_model A user defined class, that inherits from AbstractSonglist 
             *
             * @return the number of filled items.
             */
            void fill_queue(AbstractItemlist& data_model);
            void fill_playlists(AbstractItemlist& data_model);
            void fill_ouputs(AbstractItemlist& data_model);
            void fill_filelist(AbstractFilebrowser& data_model, const char * path);
            
            /**
             * @brief Send a command to the server
             *
             * The output will be printed in the cmd,
             * it is therefore just useful for debugging purpose
             *
             * @param command See the protocol reference: http://www.musicpd.org/doc/protocol/index.html
             *
             * @return true on succesfull execution
             */
            bool send_command(const char * command);
    };

}

#endif
