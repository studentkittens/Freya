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
#ifndef FREYA_SONG_GUARD
#define FREYA_SONG_GUARD

#include "mpd/client.h"
#include <glibmm.h>
namespace MPD
{
    typedef struct mpd_song mpd_song;

    class Song
    {
        public:
            Song(const mpd_song& song);
            Song(const MPD::Song& other);
            ~Song(void);

            const char * get_uri(void);
            const char * get_tag(enum mpd_tag_type type, unsigned idx);
            Glib::ustring song_format(const char* format, bool markup=true);
            unsigned get_duration(void);
            time_t get_last_modified(void);
            void set_pos(unsigned pos);
            unsigned get_pos(void);
            unsigned get_id(void);

        private:
            mpd_song * mp_Song;
            static char unknown_tag[];
    };
}

#endif
