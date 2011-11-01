#include <glibmm.h>
#include "MPDConnectionHandler.hpp"

//--------------------------------------

MPDConnectionHandler::MPDConnectionHandler() : conn()
{
    this->listener = NULL;
}

//--------------------------------------

MPDConnectionHandler::~MPDConnectionHandler()
{
    if(this->listener != NULL)
        delete this->listener;
    
    this->disconnect();
}

//--------------------------------------

mpd_connection * MPDConnectionHandler::get_connection(void)
{
    if(this->conn.is_connected())
        return this->conn.get_connection();
    else
        return NULL;
}

//--------------------------------------

IdleListener * MPDConnectionHandler::get_listener(void)
{
    if(this->conn.is_connected())
        return this->listener;
    else
        return NULL;
}

//--------------------------------------
//
gboolean MPDConnectionHandler::idle_reconnect(void)
{
    /* Did the connect work? */
    gboolean retv = this->connect();
    g_printerr("%c",(retv) ? ']' : '.');
    return (retv == false);
}

//--------------------------------------

void MPDConnectionHandler::handle_errors(enum mpd_error err)
{
    switch(err)
    {
        case MPD_ERROR_SUCCESS:
            break;
        case MPD_ERROR_CLOSED:
            this->disconnect();
            // TODO: Add a option for the reconnect interval
            g_printerr("Attempting to reconnect: [");
            Glib::signal_timeout().connect(sigc::mem_fun(*this, &MPDConnectionHandler::idle_reconnect),5000,G_PRIORITY_DEFAULT_IDLE);
            break;
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

//--------------------------------------

bool MPDConnectionHandler::check_error(void)
{
    gboolean result = false;
    if(this->conn.is_connected() == false)
        return result;

    mpd_connection * conn = this->conn.get_connection();
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

            /* Try to handle even fatal errors */
            this->handle_errors(err_code);

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
        this->conn.set_connection(mpd_conn);
        if(this->check_error())
        {
            mpd_connection_free(mpd_conn);
            this->conn.set_connection(NULL);
        }

        if(this->conn.is_connected())
        {
            this->listener = new IdleListener(mpd_conn);
            this->listener->enter();


            // TODO: Send password
        }
    }
    return this->conn.is_connected(); 
}

//--------------------------------------

bool MPDConnectionHandler::disconnect(void)
{
    if(this->conn.is_connected())
    {
        cerr << "Disconnect" << endl;
        if(this->listener != NULL)
        {
            this->listener->leave();
            delete this->listener;
            this->listener = NULL;
        }

        mpd_connection * mpd_conn = this->conn.get_connection();
        mpd_connection_free(mpd_conn);

        this->conn.set_connection(NULL);
        return true;
    }
    return false;
}

//--------------------------------------

bool MPDConnectionHandler::is_connected(void)
{
    return this->conn.is_connected();
}

//--------------------------------------
