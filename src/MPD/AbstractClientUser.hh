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
#ifndef FREYA_ABSTRACT_CLIENTUSER_GUARD
#define FREYA_ABSTRACT_CLIENTUSER_GUARD

#include "Client.hh"

class AbstractClientUser 
{
    public:
        AbstractClientUser(MPD::Client& client)
        {
            /* Save a ref. to the client */
            mp_Client = &client;

            /* Connect to client changes */
            client.signal_client_update().connect(sigc::mem_fun(*this,
                        &AbstractClientUser::on_client_update));

            /* Connect to connection change */
            client.signal_connection_change().connect(sigc::mem_fun(
                        *this,&AbstractClientUser::on_connection_change));
        }

    protected:

        /* You have to implement both of these functions. */
        virtual void on_client_update(enum mpd_idle, MPD::NotifyData& data) = 0;
        virtual void on_connection_change(bool is_connected) = 0;

        /* Setting the client is error-prone. This class does this for you. */
        MPD::Client * mp_Client;
};

#endif /* end of include guard: FREYA_BASEGELEMENT_GUARD */
