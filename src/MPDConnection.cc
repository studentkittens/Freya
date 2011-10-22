#include "MPDConnection.hpp"

//----------------------------

MPDConnection::MPDConnection(void)
{
    this->status = NULL;
    this->conn   = NULL;
}

//----------------------------

mpd_connection * MPDConnection::get_connection(void)
{
    return this->conn; 
}

//----------------------------

void MPDConnection::set_connection(mpd_connection * conn)
{
    this->conn = conn; 
}

//----------------------------

void MPDConnection::set_status(mpd_status * status)
{
    this->status = status;
}

//----------------------------

mpd_status * MPDConnection::get_status(void)
{
    return this->status;
}

//----------------------------

bool MPDConnection::is_connected(void)
{
    return !(this->conn == NULL);
}

//----------------------------
