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
#include "Connection.hh"
#include "../Log/Writer.hh"

namespace MPD
{
    //--------------------------------------

    Connection::Connection(void)
    {
        conn = NULL;
    }

    //--------------------------------------

    Connection::~Connection(void)
    {
        disconnect();
    }

    //--------------------------------------

    mpd_connection * Connection::get_connection(void)
    {
        if(is_connected())
            return conn;
        else
            return NULL;
    }

    //--------------------------------------

    bool Connection::connect(void)
    {
        /* Get connection settings */
        int timeout = CONFIG_GET_AS_INT("settings.connection.timeout") * 1000; 
        int port    = CONFIG_GET_AS_INT("settings.connection.port"); 
        Glib::ustring str_host = CONFIG_GET("settings.connection.host").c_str();

        mpd_connection * mpd_conn = mpd_connection_new(str_host.c_str(), port, timeout);
        if(mpd_conn != NULL)
        {
            conn = mpd_conn;
            if(mpd_connection_get_error(mpd_conn) != MPD_ERROR_SUCCESS)
            {
                Warning("Could not connect: %s",mpd_connection_get_error_message(conn));
                mpd_connection_free(mpd_conn);
                conn = NULL;
            }
        }
        return is_connected();
    }

    //--------------------------------------

    bool Connection::disconnect(void)
    {
        if(is_connected())
        {
            Info("Disconnecting");
            mpd_connection_free(conn);
            conn = NULL;
            return true;
        }
        return false;
    }

    //--------------------------------------

    bool Connection::is_connected(void)
    {
        return !(conn == NULL);
    }

    //--------------------------------------
    
    bool Connection::clear_error(void)
    {
        bool retv = false;
        if(conn != NULL) 
        {
            enum mpd_error err_code = mpd_connection_get_error(conn);
            if(err_code != MPD_ERROR_SUCCESS)
            {
                if((retv = mpd_connection_clear_error(conn)) == false)
                {
                    const char * err_string = mpd_connection_get_error_message(conn);
                    Warning("Cannot recover from error: %s",err_string);
                }
            }
        }
        return retv;
    }

    //--------------------------------------
}
