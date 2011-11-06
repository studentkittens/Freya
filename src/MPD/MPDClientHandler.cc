#include "MPDClientHandler.hh"

// Helper function
mpd_connection * MPDClientHandler::get_conn_by_obj(void)
{
    mpd_connection * mpd_conn = NULL;
    mpd_conn = this->conn.get_connection();
    return mpd_conn;
}


MPDClientHandler::MPDClientHandler() : conn()
{
    this->conn.connect();
}

//-------------------------------

MPDClientHandler::~MPDClientHandler()
{
    this->conn.disconnect();
}

//-------------------------------

void MPDClientHandler::go_idle(void)
{
    IdleListener * listener = this->conn.get_listener();
    if(listener != NULL)
    {
        listener->enter();
    }
    this->conn.check_error();
}

//-------------------------------

void MPDClientHandler::go_busy(void)
{
    IdleListener * listener = this->conn.get_listener();
    if(listener != NULL)
    {
        listener->leave();
    }
    this->conn.check_error();
}

//-------------------------------
//-------------------------------

bool MPDClientHandler::send_command(const char * command)
{
    bool result = false;
    if(command != NULL && this->conn.is_connected())
    {
        /* Go into active mode */
        go_busy();

        /* Send the command - throw away response */
        mpd_connection * mpd_conn = this->get_conn_by_obj();
        mpd_send_command(mpd_conn,command,NULL);
        result = mpd_response_finish(mpd_conn);

        /* Go back listening */
        go_idle();
    }
    return result;
}

//-------------------------------

void MPDClientHandler::list_queue(void)
{
    go_busy();

    mpd_connection * conn = get_conn_by_obj();
    if(conn && mpd_send_list_queue_meta(conn) != FALSE)
    {
        mpd_pair * pair = NULL;
        while((pair = mpd_recv_pair(conn)))
        {
            //g_printerr("%s => %s\n",pair->name,pair->value);
            mpd_return_pair(conn,pair);
        }
    }

    g_print("Done.\n");

    go_idle();
}

//-------------------------------

MPDConnectionHandler * MPDClientHandler::get_connection_handler(void)
{
    return &(this->conn);
}
