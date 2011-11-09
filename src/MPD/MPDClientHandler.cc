#include "MPDClientHandler.hh"

// Helper function
mpd_connection * MPDClientHandler::get_conn_by_obj(void)
{
    mpd_connection * mpd_conn = NULL;
    mpd_conn = this->conn.get_connection();
    return mpd_conn;
}

//-------------------------------

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

bool MPDClientHandler::playback_play(void)
{
    return this->send_command("play");
}

//-------------------------------

bool MPDClientHandler::playback_stop(void)
{
    return this->send_command("stop");
}

//-------------------------------

bool MPDClientHandler::playback_next(void)
{
    return this->send_command("next");
}

//-------------------------------

bool MPDClientHandler::playback_prev(void)
{
    return this->send_command("next");
}

//-------------------------------

bool MPDClientHandler::playback_pause(void)
{
    return this->send_command("pause");
}

//-------------------------------

void MPDClientHandler::list_queue(void)
{
    go_busy();

    mpd_connection * conn = get_conn_by_obj();
    if(conn && mpd_send_list_queue_meta(conn) != FALSE)
    {
        mpd_entity * ent = NULL;
        while((ent = mpd_recv_entity(conn)))
        {
            switch(mpd_entity_get_type(ent))
            {
                case MPD_ENTITY_TYPE_UNKNOWN:
                    
                    break;
                case MPD_ENTITY_TYPE_DIRECTORY:
                    break;
                case MPD_ENTITY_TYPE_SONG:
                {
                    const mpd_song * song = mpd_entity_get_song(ent);
                    g_message("%s - %s - %s",
                            mpd_song_get_tag(song,MPD_TAG_ARTIST,0),
                            mpd_song_get_tag(song,MPD_TAG_ALBUM,0),
                            mpd_song_get_tag(song,MPD_TAG_TITLE,0)
                            );
                    break;
                }
                case MPD_ENTITY_TYPE_PLAYLIST:
                    break;
            }
            mpd_entity_free(ent);
        }
    }
    go_idle();
}

//-------------------------------

MPDConnectionHandler * MPDClientHandler::get_connection_handler(void)
{
    return &(this->conn);
}
