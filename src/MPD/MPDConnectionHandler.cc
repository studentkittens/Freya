#include <glibmm.h>
#include "MPDConnectionHandler.hh"
#include "../LogHandler/LogHandler.hh"

//--------------------------------------

MPDConnectionHandler::MPDConnectionHandler()
{
    this->listener = NULL;
    this->current_status = NULL;
    this->conn = NULL;
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
    if(this->is_connected())
        return this->conn;
    else
        return NULL;
}

//--------------------------------------

IdleListener * MPDConnectionHandler::get_listener(void)
{
    if(this->is_connected())
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
    if(retv == true)
    {
        Info("Succesfully reconnected.");
    }
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
        Info("Starting reconnect campaign. Will try again every few seconds.");
        Glib::signal_timeout().connect(sigc::mem_fun(*this, &MPDConnectionHandler::idle_reconnect),1000,G_PRIORITY_DEFAULT_IDLE);
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
    if(this->is_connected() == false)
        return result;

    if(is_connected())
    {
        /* Check for errors at this connection and log them */
        if(mpd_connection_get_error(conn) != MPD_ERROR_SUCCESS)
        {
            enum mpd_error err_code = mpd_connection_get_error(conn);
            if(err_code == MPD_ERROR_SERVER)
            {
                Warning("ServerErrorId #%d: ",mpd_connection_get_server_error(conn));
            }
            else
            {
                Warning("Error #%d: ",err_code);
            }

            Warning("%s",mpd_connection_get_error_message(conn));

            /* Clear nonfatal errors */
            if(mpd_connection_clear_error(conn) == false)
            {
                Fatal("Mentioned error is fatal.");
                Fatal("Freya will shutdown now therefore.");
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
        this->conn = mpd_conn;
        if(this->check_error())
        {
            mpd_connection_free(mpd_conn);
            this->conn = NULL;
        }

        if(this->is_connected())
        {
            this->listener = new IdleListener(mpd_conn);

            /* Enter blocking mode */
            this->listener->enter();
        }
    }
    return this->is_connected();
}

//--------------------------------------

bool MPDConnectionHandler::disconnect(void)
{
    if(this->is_connected())
    {
        Info("Disconnecting");
        if(this->listener != NULL)
        {
            this->listener->leave();
            delete this->listener;
            this->listener = NULL;
        }

        mpd_connection_free(this->conn);
        this->conn = NULL;
        return true;
    }
    return false;
}

//--------------------------------------

bool MPDConnectionHandler::is_connected(void)
{
    return !(this->conn == NULL);
}

//--------------------------------------
