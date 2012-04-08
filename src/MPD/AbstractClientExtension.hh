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
#ifndef FREYA_ABSTRACTCLIENTEXTENSION_HH
#define FREYA_ABSTRACTCLIENTEXTENSION_HH

namespace MPD
{
class BaseClient;

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
    AbstractClientExtension(BaseClient& base_client)
    {
        mp_BaseClient = &base_client;
    }

protected:

    BaseClient * mp_BaseClient;
};

/* Get the mpd_connection */
#define get_c_connection()                             \
    (mp_BaseClient->is_connected()) ?                  \
    mp_BaseClient->get_connection().get_connection() : \
    NULL

/* Go into active mode */
#define EXTERNAL_GET_BUSY             \
    if(mp_BaseClient->is_connected()) \
    {                                 \
        mp_BaseClient->go_busy();     \
        mpd_connection * conn =       \
         get_c_connection();          \
        if(conn != NULL) {

/* Go back idling, *never* forget this */
#define EXTERNAL_GET_LAID     \
    }                         \
    mp_BaseClient->go_idle(); \
    }

}

#endif /* end of include guard: FREYA_ABSTRACTCLIENTEXTENSION_HH */
