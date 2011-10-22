#include "MPDClientHandler.hpp"

// Helper function
mpd_connection * MPDClientHandler::get_conn_by_obj(void)
{
    mpd_connection * mpd_conn = NULL;
    if(this->conn != NULL)
    {
        mpd_conn = this->conn->get_connection();
    }
    return mpd_conn;
}


MPDClientHandler::MPDClientHandler()
{
    this->conn = new MPDConnectionHandler();
    this->conn->connect();
}

//-------------------------------

MPDClientHandler::~MPDClientHandler()
{
    this->conn->disconnect();
    delete this->conn;
}

//-------------------------------

void MPDClientHandler::go_idle(void)
{
    IdleListener * listener = this->conn->get_listener();
    if(listener != NULL)
    {
        listener->enter();
    }
    this->conn->check_error();
}

//-------------------------------

void MPDClientHandler::go_busy(void)
{
    IdleListener * listener = this->conn->get_listener();
    if(listener != NULL)
    {
        listener->leave();
    }
    this->conn->check_error();
}

//-------------------------------
//-------------------------------

bool MPDClientHandler::send_command(const char * command)
{
    bool result = false;
    if(command != NULL)
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
