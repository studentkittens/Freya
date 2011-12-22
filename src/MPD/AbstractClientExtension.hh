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
#ifndef FREYA_ABSTRACTCLIENTEXTENSION_HH
#define FREYA_ABSTRACTCLIENTEXTENSION_HH

#include "BaseClient.hh"

namespace MPD
{
    /**
     * @brief Abstract base class for classes that want to implement spefic MPD Commands.
     */
    class AbstractClientExtension
    {
        public:

            /**
             * @brief ClientExtensions need a reference to the Client.
             *
             * @param base_client a reference to the MPD::Client
             */
            AbstractClientExtension(MPD::BaseClient& base_client)
            {
                mp_BaseClient = &base_client;
            }

        protected:

            MPD::BaseClient * mp_BaseClient;

            /**
             * @brief Get the underlying C struct
             *
             * @return a pointer to a valid mpd_connection
             */
            mpd_connection * get_c_connection()
            {
                g_assert(mp_BaseClient);
                if(mp_BaseClient->is_connected())
                {
                    MPD::Connection& conn = mp_BaseClient->get_connection();
                    return conn.get_connection();
                }
                else
                {
                    return NULL;
                }
            }
    };

    /* Go into active mode */
    #define EXTERNAL_GET_BUSY                   \
            if(mp_BaseClient->is_connected())   \
            {                                   \
                mp_BaseClient->go_busy();       \
                mpd_connection * conn =         \
                get_c_connection();             \
                if(conn != NULL) {              

    /* Go back idling, *never* forget this */                
    #define EXTERNAL_GET_LAID             \
                }                         \
                mp_BaseClient->go_idle(); \
            }                             

}

#endif /* end of include guard: FREYA_ABSTRACTCLIENTEXTENSION_HH */
