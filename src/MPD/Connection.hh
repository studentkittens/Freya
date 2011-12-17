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
#ifndef FREYA_MPDCONNECTION_GUARD
#define FREYA_MPDCONNECTION_GUARD

#include <mpd/client.h>
#include <glibmm.h>

namespace MPD
{
    typedef sigc::signal<  
                         void, /* No interaction */
                         bool, /* is_fatal       */
                         mpd_error
                        >ErrorNotify;

    class Connection
    {
        public:

            /* Publicinstance */
            Connection(void);
            ~Connection(void);

            /* Init */
            bool is_connected(void);
            bool connect(void);
            bool disconnect(void);
            bool clear_error(void);
            bool check_error(void);
            ErrorNotify& signal_error(void);

            /* Returns mpd_conn */
            mpd_connection * get_connection(void);

        private:

            /* The connection from libmpdclient to MPD
            */
            mpd_connection * conn;

            /* Emit is called on this when check_error() 
             * reports an error */
            ErrorNotify m_ErrorSig;
    };

}

#endif
