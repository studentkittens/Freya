#include <glibmm.h>
#include "MPDConnectionHandler.hpp"

//--------------------------------------

MPDConnectionHandler::MPDConnectionHandler()
{
    this->listener = NULL;
    this->conn     = new MPDConnection();
}

//--------------------------------------

MPDConnectionHandler::~MPDConnectionHandler()
{
    if(this->listener != NULL)
        delete this->listener;
    
    this->disconnect();

    if(this->conn != NULL)
        delete this->conn;
}

//--------------------------------------

mpd_connection * MPDConnectionHandler::get_connection(void)
{
    if(this->conn->is_connected())
        return this->conn->get_connection();
    else
        return NULL;
}

//--------------------------------------

IdleListener * MPDConnectionHandler::get_listener(void)
{
    if(this->conn->is_connected())
        return this->listener;
    else
        return NULL;
}

//--------------------------------------

bool MPDConnectionHandler::check_error(void)
{
    gboolean result = false;
    if(this->conn->is_connected() == false)
        return result;

    mpd_connection * conn = this->conn->get_connection();
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

bool MPDConnectionHandler::connect(void)
{
    mpd_connection * mpd_conn = mpd_connection_new("localhost", 6600, 30000);
    if(mpd_conn != NULL)
    {
        this->conn->set_connection(mpd_conn);
        if(this->check_error())
        {
            mpd_connection_free(mpd_conn);
            this->conn->set_connection(NULL);
        }

        if(this->conn->is_connected())
        {
            this->listener = new IdleListener(mpd_conn);
            // TODO: Check if already connected.
            // TODO: Send password
            this->listener->enter();
        }
    }
    return this->conn->is_connected(); 
}

//--------------------------------------

bool MPDConnectionHandler::disconnect(void)
{
    if(this->conn->is_connected())
    {
        cerr << "Disconnect" << endl;
        mpd_connection * mpd_conn = this->conn->get_connection();
        mpd_connection_free(mpd_conn);
        this->conn->set_connection(NULL);
        return true;
    }
    return false;
}

//--------------------------------------
