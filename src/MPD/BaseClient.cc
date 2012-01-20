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
#include "BaseClient.hh"
#include "../Log/Writer.hh"
#include "../Config/Handler.hh"

namespace MPD
{
    BaseClient::BaseClient() :
        m_Conn(),
        mp_Listener(NULL),
        m_ListBegun(false)
    {
        /* Call handle_errors on any found error */
        m_Conn.signal_error().connect(
            sigc::mem_fun(*this,&BaseClient::handle_errors));
    }

//-------------------------------

    bool BaseClient::__connect()
    {
        if(m_Conn.is_connected() == false)
        {
            if(m_Conn.connect())
            {
                mp_Listener = new MPD::Listener(&m_Notifier,m_Conn);
                go_idle();
                force_update();
            }
            m_Conn.emit_connection_change();
        }

        return is_connected();
    }

//-------------------------------

    bool BaseClient::__disconnect()
    {
        if(m_Conn.is_connected())
        {
            if(mp_Listener)
            {
                if(mp_Listener != NULL)
                {
                    mp_Listener->leave();
                    delete mp_Listener;
                    mp_Listener = NULL;
                }
            }
            m_Conn.disconnect();
            m_Conn.emit_connection_change();
        }
        return is_connected();
    }

//-------------------------------

    void BaseClient::go_idle()
    {
        m_Conn.check_error();
        if(mp_Listener && mp_Listener->is_idling() == false)
        {
            mp_Listener->enter();
        }
    }

//-------------------------------

    void BaseClient::go_busy()
    {
        if(mp_Listener && mp_Listener->is_idling() == true)
        {
            mp_Listener->leave();
        }
        m_Conn.check_error();
    }

//-------------------------------

    Connection& BaseClient::get_connection()
    {
        return m_Conn;
    }

//-------------------------------

    bool BaseClient::is_connected()
    {
        return m_Conn.is_connected();
    }

//-------------------------------

    void BaseClient::begin()
    {
        if(is_connected())
        {
            go_busy();
            m_ListBegun = true;
            mpd_command_list_begin(m_Conn.get_connection(),true);
        }
    }

//-------------------------------

    void BaseClient::commit()
    {
        if(is_connected())
        {
            mpd_connection * conn = m_Conn.get_connection();
            mpd_command_list_end(conn);
            mpd_response_finish(conn);
            m_ListBegun = false;
            go_idle();
        }
    }

//--------------------

    Status * BaseClient::get_status()
    {
        if(m_Conn.is_connected())
        {
            return &(mp_Listener->get_data().get_status());
        }
        return NULL;
    }

//--------------------

    EventNotifier& BaseClient::signal_client_update()
    {
        return m_Notifier;
    }

//--------------------

    ConnectionNotifier& BaseClient::signal_connection_change()
    {
        return m_Conn.signal_connection_change();
    }

//--------------------

    void BaseClient::force_update()
    {
        if(m_Conn.is_connected())
            mp_Listener->force_update();
    }

//-------------------------------

    gboolean BaseClient::timeout_reconnect()
    {
        Info("Trying to stand up");
        gboolean retv = __connect();
        Info("Sigh.");

        if(retv)
        {
            Info("Succesfully reconnected.");
        }
        return (retv == false);
    }

//-------------------------------

    void BaseClient::handle_errors(bool is_fatal, mpd_error err)
    {
        switch(err)
        {
        case MPD_ERROR_SUCCESS:
        {
            break;
        }
        case MPD_ERROR_CLOSED:
        {
            /* Make sure to be disconnected first */
            __disconnect();

            /* Get the reconnectinterval in seconds */
            int interval = CONFIG_GET_AS_INT("settings.connection.reconnectinterval") * 1000;

            /* Schedule reconnect */
            Glib::signal_timeout().connect(
                sigc::mem_fun(*this, &BaseClient::timeout_reconnect),
                interval,G_PRIORITY_DEFAULT_IDLE);

            Info("Starting reconnect campaign. Will try again every %d seconds.",interval);
            break;
        }
        case MPD_ERROR_SERVER:
        case MPD_ERROR_OOM:
        case MPD_ERROR_ARGUMENT:
        case MPD_ERROR_STATE:
        case MPD_ERROR_TIMEOUT:
        case MPD_ERROR_SYSTEM:
        case MPD_ERROR_RESOLVER:
        case MPD_ERROR_MALFORMED:
        default:
            break;
        }
    }
}
