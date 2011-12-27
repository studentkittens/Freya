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
#ifndef DIRECTORY_FY7WZEO9
#define DIRECTORY_FY7WZEO9

#include <mpd/client.h>

namespace MPD
{
    /**
     * @brief A wrapper for mpd_directory
     */
    class Directory 
    {
        public:
            /**
             * @brief You are not supposed to instace this yourself.
             *
             * @param dir
             */
            Directory(mpd_directory& dir);
            /**
             * @brief dtor will free underlying mpd_directory
             */
            virtual ~Directory(void);

            /**
             * @brief The path of the directory
             *
             * @return a string
             */
            const char * get_path(void);

        private:

            mpd_directory * mp_Dir;
    };
}

#endif /* end of include guard: DIRECTORY_FY7WZEO9 */
