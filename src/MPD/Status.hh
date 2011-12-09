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
#ifndef FREYA_MPD_STATUS
#define FREYA_MPD_STATUS

#include <mpd/client.h>

namespace MPD
{
    typedef enum mpd_state mpd_state;

    /* C++ Wrapper for mpd_status */
    class Status
    {
        public: 

            Status(mpd_status& status,unsigned long nextSongID);
            ~Status(void);

            /* -------- */

            int get_volume(void);
            bool get_repeat(void);
            bool get_random(void);
            bool get_single(void);
            bool get_consume(void);
            unsigned get_queue_length(void);
            unsigned get_queue_version(void);
            mpd_state get_state(void);
            unsigned get_crossfade(void);
            float get_mixrampdb(void);
            float get_mixrampdelay(void);
            int get_song_pos(void);
            int get_song_id(void);
            unsigned get_elapsed_time(void);
            unsigned get_elapsed_ms(void);
            unsigned get_total_time(void);
            unsigned get_kbit_rate(void);
            unsigned get_update_id(void);
            const char * get_error(void);

            uint32_t get_audio_sample_rate(void);
            uint8_t get_audio_bits(void);
            uint8_t get_audio_channels(void);

        private: 

            mpd_status * m_Status;
    };
}

#endif
