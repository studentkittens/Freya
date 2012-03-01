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
#include "NotifyData.hh"
#include "../Log/Writer.hh"

namespace MPD
{
    NotifyData::NotifyData(MPD::Connection& p_conn)
    {
        mp_Conn = &p_conn;
        mp_Status = NULL;
        mp_Statistics = NULL;
        mp_Song = NULL;
        mp_NextSong = NULL;
    }

    //------------------

    NotifyData::~NotifyData()
    {
        delete mp_Statistics;
        delete mp_Status;
        delete mp_Song;
        delete mp_NextSong;
    }

    //------------------

    /* Since libmpdclient does not support the next-song-id,
     * we habe to improvise a little bit.
     */
    Status * NotifyData::recv_status_own()
    {
        struct mpd_status * status = NULL;
        struct mpd_connection * conn = NULL;
        struct mpd_pair *pair = NULL;
        Status * retv_status = NULL;
        unsigned long NextSongID = 0;

        if(mp_Conn->is_connected())
        {
            conn = mp_Conn->get_connection();
            status = mpd_status_begin();
            if(status != NULL)
            {
                while ((pair = mpd_recv_pair(conn)) != NULL)
                {
                    if(!g_ascii_strcasecmp(pair->name,"nextsongid"))
                    {
                        NextSongID = g_ascii_strtoll(pair->value,NULL,10);
                    }
                    else
                    {
                        mpd_status_feed(status, pair);
                    }
                    mpd_return_pair(conn, pair);
                }
            }

            if(status != NULL)
            {
                retv_status = new Status(*status,NextSongID);
            }

            if(mp_NextSong != NULL)
            {
                delete mp_NextSong;
                mp_NextSong = NULL;
            }

            mpd_song * c_next_song = mpd_run_get_queue_song_id(conn,NextSongID);
            if(c_next_song != NULL)
            {
                mp_NextSong = new Song(*c_next_song);
            }
            else
            {
                mp_Conn->clear_error();
            }
        }
        return retv_status;
    }

    //------------------

    Status& NotifyData::get_status()
    {
        /* This should never be NULL. */
        g_assert(mp_Status);
        return *(mp_Status);
    }

    //------------------

    Statistics& NotifyData::get_statistics()
    {
        /* This should never be NULL. */
        g_assert(mp_Statistics);
        return *(mp_Statistics);
    }

    //------------------

    Song * NotifyData::get_song()
    {
        return mp_Song;
    }

    //------------------

    Song * NotifyData::get_next_song()
    {
        return mp_NextSong;
    }

    //------------------

    void NotifyData::update_all(unsigned event)
    {
        if(mp_Conn->is_connected())
        {
            mpd_connection * mpd_conn = mp_Conn->get_connection();

            /*-------------------------------*/

            if(event & MPD_IDLE_PLAYER)
            {
                delete mp_Song;
                mp_Song = NULL;

                mpd_song * c_song = mpd_run_current_song(mpd_conn);
                if(c_song)
                    mp_Song = new Song(*c_song);
            }

            /*-------------------------------*/

            if(event & (MPD_IDLE_DATABASE|MPD_IDLE_UPDATE))
            {
                delete mp_Statistics;
                mp_Statistics = NULL;

                mpd_stats * c_stats = mpd_run_stats(mpd_conn);
                if(c_stats)
                    mp_Statistics = new Statistics(*c_stats);
            }

            /*-------------------------------*/

            if(event & (MPD_IDLE_PLAYER|MPD_IDLE_OPTIONS|MPD_IDLE_MIXER|MPD_IDLE_OUTPUT|MPD_IDLE_QUEUE))
            {
                delete mp_Status;
                mp_Status = NULL;

                mpd_send_status(mpd_conn);
                mp_Status = recv_status_own();
            }
        }
    }
}
