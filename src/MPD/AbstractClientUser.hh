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
        /**
         * @brief Pass a MPD::Client ref to register it's signals and maintain a pointer to it
         *
         * @param client a ref to a MPD::Client
         */
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

        /**
         * @brief Derived class have to implement this
         *
         * It is called once the Listener notices any changed
         *
         * @param mpd_idle the type of the change (see http://www.musicpd.org/doc/libmpdclient/idle_8h.html#a3378f7a24c714d7cb1058232330d7a1c)
         * @param data a reference to MPD::NotifyData, for use with get_status() etc.
         */
        virtual void on_client_update(enum mpd_idle, MPD::NotifyData& data) = 0;
        /**
         * @brief Derived class have to implement this 
         *
         * Called once the Client connects or disconnects
         * server_changed can only be true when is_connected is true 
         *
         * @param server_changed true if the server changed on connect
         * @param is_connected true if connected 
         */
        virtual void on_connection_change(bool server_changed, bool is_connected) = 0;

        /**
         * @brief Setting the client is error-prone. This class does this for you.
         */
        MPD::Client * mp_Client;
};

#endif /* end of include guard: FREYA_BASEGELEMENT_GUARD */
