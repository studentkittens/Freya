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
#ifndef INIT_PATH_GUARD
#define INIT_PATH_GUARD

#include <glibmm/ustring.h>

namespace Init
{

    /**
     * @brief Get the path to files Freya will write to (Config/Log)
     */
    class Path
    {
    public:
        Path ();
        ~Path ();

        /**
         * @brief returns absolute path to config dir e.g. /home/user/.config/freya
         *
         * @return config dir path as ustring
         */
        Glib::ustring get_config_dir();


        /**
         * @brief returns absolute path to config file e.g. /home/user/.config/freya/config.xml
         *
         * @return config file path as ustring
         */
        Glib::ustring path_to_config();


        /**
         * @brief returns absolute path log file e.g. ~/.config/freya/log.txt
         *
         * @return log file path as ustring
         */
        Glib::ustring path_to_log();

    private:
        void create_config();
        void create_dir();
        void dir_is_avaiable();
        char* configfile;
        char* configdir;
    };
}
#endif /* end of include guard: INIT_SP0811FS */
