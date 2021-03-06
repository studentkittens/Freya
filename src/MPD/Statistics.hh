/***********************************************************
* This file is part of Freya
* - A free MPD Gtk3 MPD Client -
*
* Authors: Christopher Pahl, Christoph Piechula,
*          Eduard Schneider
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
#ifndef FREYA_STATISTICS_GUARD
#define FREYA_STATISTICS_GUARD

#include <mpd/client.h>
#include "../Utils/UseMemPool.hh"

namespace MPD
{
/**
 * @brief A wrapper for mpd_stats
 */
class Statistics : public UseMemPool<Statistics>
{
public:

    /**
     * @brief You are not supposed to instance this yourself
     *
     * @param stats
     */
    Statistics(mpd_stats& stats);
    ~Statistics();

    /**
     * @brief Number of artists in DB
     *
     * @return
     */
    unsigned get_number_of_artists();
    /**
     * @brief Number of albums in DB
     *
     * @return
     */
    unsigned get_number_of_albums();
    /**
     * @brief Number of songs in DB
     *
     * @return
     */
    unsigned get_number_of_songs();
    /**
     * @brief Get uptime in seconds
     *
     * @return
     */
    unsigned long get_uptime();
    /**
     * @brief get seconds since last update
     *
     * @return
     */
    unsigned long get_db_update_time();
    /**
     * @brief Playing since xxx seconds
     *
     * @return
     */
    unsigned long get_play_time();
    /**
     * @brief Total time in seconds needed to play the whole DB
     *
     * @return
     */
    unsigned long get_db_play_time();

private:

    mpd_stats * mp_Statistics;
};
}

#endif
