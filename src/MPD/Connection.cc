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
}
