#include <glibmm.h>
#include "MPDClient.hpp"

//--------------------------------------

MPDClient::MPDClient()
{
    this->idle_observer = NULL;
    this->mpd_conn = NULL;
}

//--------------------------------------

MPDClient::~MPDClient()
{
    if(this->idle_observer != NULL)
    {
        delete this->idle_observer;
    }
    this->disconnect();
}

//--------------------------------------

mpd_connection * MPDClient::get_connection(void)
{
    return this->mpd_conn;
}

//--------------------------------------

bool MPDClient::check_error(void)
{
    gboolean result = false;
    mpd_connection * conn = this->get_connection();
    if(conn != NULL)
    {
        /* Check for errors at this connection and log them */
        if(mpd_connection_get_error(conn) != MPD_ERROR_SUCCESS)
        {
            enum mpd_error err_code = mpd_connection_get_error(conn);
            if(err_code == MPD_ERROR_SERVER) {
                g_printerr("ServerError #%d: ",mpd_connection_get_server_error(conn));
            } else {
                g_printerr("Error #%d: ",err_code);
            }
            g_printerr("%s\n",mpd_connection_get_error_message(conn));

            /* Clear nonfatal errors */
            if(mpd_connection_clear_error(conn) == false)
            {
                g_printerr("Mentioned error is fatal.\n");
            }

            /* An error occured */
            result = true;
        }
    }
    return result;
}

//--------------------------------------

bool MPDClient::connect(void)
{
    this->mpd_conn = mpd_connection_new("localhost", 6600, 30000);
    if(this->check_error())
    {
        mpd_connection_free(this->mpd_conn);
        this->mpd_conn = NULL;
    }

    if(this->mpd_conn != NULL)
    {
        this->idle_observer = new IdleListener(this->get_connection());
        this->idle_observer->enter();
        // TODO: Check if already connected.
        // TODO: Send password
        // TODO: Save FD (for polling?)
    }
    return !(this->mpd_conn == NULL);    
}

//--------------------------------------

bool MPDClient::disconnect(void)
{
    if(this->get_connection())
    {
        mpd_connection_free(this->mpd_conn);
        this->mpd_conn = NULL;
        return true;
    }
    return false;
}

//--------------------------------------
