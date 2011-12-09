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
#include "Statistics.hh"

namespace MPD
{
    Statistics::Statistics(mpd_stats& statistics)
    {
        mp_Statistics = &statistics;
    }

    Statistics::~Statistics(void)
    {
        if(mp_Statistics)
        {
            mpd_stats_free(mp_Statistics);
        }
    }

    unsigned Statistics::get_number_of_artists(void)
    {
        return mpd_stats_get_number_of_artists(mp_Statistics);
    }

    unsigned Statistics::get_number_of_albums(void)
    {
        return mpd_stats_get_number_of_albums(mp_Statistics);
    }

    unsigned Statistics::get_number_of_songs(void)
    {
        return mpd_stats_get_number_of_songs(mp_Statistics);
    }

    unsigned long Statistics::get_uptime(void)
    {
        return mpd_stats_get_uptime(mp_Statistics);
    }

    unsigned long Statistics::get_db_update_time(void)
    {
        return mpd_stats_get_db_update_time(mp_Statistics);
    }

    unsigned long Statistics::get_play_time(void)
    {
        return mpd_stats_get_play_time(mp_Statistics);
    }

    unsigned long Statistics::get_db_play_time (void)
    {
        return mpd_stats_get_db_play_time(mp_Statistics);
    }
}
