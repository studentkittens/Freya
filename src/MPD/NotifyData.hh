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
#ifndef FREYA_NOTIFYDATA_GUARD
#define FREYA_NOTIFYDATA_GUARD

#include "Connection.hh"
#include "Statistics.hh"
#include "Status.hh"
#include "Song.hh"

namespace MPD
{
    class NotifyData
    {
        public:
            NotifyData(Connection& conn);
            ~NotifyData(void);

            Status& get_status(void);
            Statistics& get_statistics(void);

            /* These return pointers since they can be NULL!
             * Check for it therefore. */
            Song * get_song(void);
            Song * get_next_song(void);

            /**
             * @brief Update internal client state
             */
            void update_all(void);

        private:

            /**
             * @brief Custom implementation of mpd_run_status()
             *
             * @return same as mpd_run_status(), but sets m_NextSongID
             */
            Status * recv_status_own(void);
            
            /**
             * @brief Current valid connection.
             */
            Connection * mp_Conn;

            /**
             * @brief The mpd status (wrapped to C++ object)
             */
            Status * mp_Status;
            /**
             * @brief MPD statistics (wrapped to C++ object)
             */
            Statistics * mp_Statistics;
            /**
             * @brief Currently playing song (wrapped to C++ object)
             */
            Song * mp_Song;
            Song * mp_NextSong;
    };
}

#endif
