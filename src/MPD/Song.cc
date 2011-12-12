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
#include "Song.hh"

namespace MPD
{
    Song::Song(const mpd_song& song)
    {
        mp_Song = (mpd_song*)&song;
    }
    
    /*------------------------------*/
    
    Song::Song(const MPD::Song& other)
    {
       mpd_song * other_song = other.mp_Song;
       if(other_song != NULL)
           mp_Song = mpd_song_dup(other_song);
       else
           mp_Song = NULL;
    }
    
    /*------------------------------*/
    
    Song::~Song(void)
    {
        mpd_song_free(mp_Song);
    }

    /*------------------------------*/

    const char * Song::get_uri(void)
    {
        return mpd_song_get_uri(mp_Song);
    }
    /*------------------------------*/

    const char * Song::get_tag(enum mpd_tag_type type, unsigned idx)
    {
        return mpd_song_get_tag(mp_Song,type,idx);

    }
    /*------------------------------*/

    unsigned Song::get_duration(void)
    {
        return mpd_song_get_duration(mp_Song);

    }
    /*------------------------------*/

    time_t Song::get_last_modified(void)
    {
        return mpd_song_get_last_modified(mp_Song);

    }
    /*------------------------------*/

    void Song::set_pos(unsigned pos)
    {
        mpd_song_set_pos(mp_Song,pos);

    }
    /*------------------------------*/

    unsigned Song::get_pos(void)
    {
        return mpd_song_get_pos(mp_Song);

    }
    /*------------------------------*/

    unsigned Song::get_id(void)
    {
        return mpd_song_get_id(mp_Song);
    }
    /*------------------------------*/
}
