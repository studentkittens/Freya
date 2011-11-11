#include <glibmm.h>
#include "Connection.hh"
#include "../LogHandler/LogHandler.hh"

namespace MPD
{
    //--------------------------------------

    Connection::Connection(void)
    {
        current_status = NULL;
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
        mpd_connection * mpd_conn = mpd_connection_new("localhost", 6600, 30000);
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
}
