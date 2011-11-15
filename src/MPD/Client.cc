#include "Client.hh"

namespace MPD
{
    //-------------------------------

    Client::Client() : conn(), m_Notifier()
    {
        connect();
    }

    //-------------------------------

    Client::~Client()
    {
        disconnect();
    }

    //-------------------------------

    void Client::connect(void)
    {
        if(conn.connect())
        {
            Info("Creating Listener");
            listener = new Listener(&m_Notifier,conn);
            go_idle();
        }
    }

    //-------------------------------

    void Client::disconnect(void)
    {
        if(listener)
        {
            if(listener != NULL)
                delete listener;

            conn.disconnect();
        }
    }

    //-------------------------------

    void Client::go_idle(void)
    {
        listener->enter();
        check_error();
    }

    //-------------------------------

    void Client::go_busy(void)
    {
        listener->leave();
        check_error();
    }

    //-------------------------------
    //-------------------------------

    bool Client::send_command(const char * command)
    {
        bool result = false;
        if(command != NULL && conn.is_connected())
        {
            /* Go into active mode */
            go_busy();

            /* Send the command - throw away response */
            mpd_connection * mpd_conn = conn.get_connection();
            mpd_send_command(mpd_conn,command,NULL);

            mpd_pair * ent = NULL;
            while((ent = mpd_recv_pair(mpd_conn)))
            {
                g_printerr("%s => %s\n",ent->name,ent->value);
                mpd_return_pair(mpd_conn,ent);
            }

            /* Go back listening */
            go_idle();
        }
        return result;
    }

    //-------------------------------

    bool Client::playback_play(void)
    {
        return this->send_command("play");
    }

    //-------------------------------

    bool Client::playback_stop(void)
    {
        return this->send_command("stop");
    }

    //-------------------------------

    bool Client::playback_next(void)
    {
        return this->send_command("next");
    }

    //-------------------------------

    bool Client::playback_prev(void)
    {
        return this->send_command("previous");
    }

    //-------------------------------

    bool Client::playback_pause(void)
    {
        return this->send_command("pause");
    }

    //-------------------------------

    void Client::list_queue(void)
    {
        go_busy();

        mpd_connection * mpd_conn = conn.get_connection();
        if(mpd_conn && mpd_send_list_queue_meta(mpd_conn) != FALSE)
        {
            mpd_entity * ent = NULL;
            while((ent = mpd_recv_entity(mpd_conn)))
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

    gboolean Client::timeout_reconnect(void)
    {
        connect();

        gboolean retv = conn.is_connected();
        if(retv)
        {
            Info("Succesfully reconnected.");
        }
        return (retv == false);
    }

    //-------------------------------

    void Client::handle_errors(enum mpd_error err)
    {
        switch(err)
        {
            case MPD_ERROR_SUCCESS:
                {
                    break;
                }
            case MPD_ERROR_CLOSED:
                {
                    disconnect();
                    int interval = CONFIG_GET_AS_INT("settings.connection.reconnectinterval");
                    Glib::signal_timeout().connect(sigc::mem_fun(*this, &Client::timeout_reconnect),interval,G_PRIORITY_DEFAULT_IDLE);
                    Info("Starting reconnect campaign. Will try again every %d seconds.",interval);
                    break;
                }
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

    bool Client::check_error(void)
    {
        bool result = false;
        if(conn.is_connected())
        {
            /* Check for errors at this connection and log them */
            mpd_connection * mpd_conn = conn.get_connection();
            if(mpd_connection_get_error(mpd_conn) != MPD_ERROR_SUCCESS)
            {
                enum mpd_error err_code = mpd_connection_get_error(mpd_conn);
                if(err_code == MPD_ERROR_SERVER)
                {
                    Warning("ServerErrorId #%d: ",mpd_connection_get_server_error(mpd_conn));
                }
                else
                {
                    Warning("Error #%d: ",err_code);
                }

                Warning("%s",mpd_connection_get_error_message(mpd_conn));

                /* Clear nonfatal errors */
                if(mpd_connection_clear_error(mpd_conn) == false)
                {
                    Fatal("Mentioned error is fatal.");
                }

                /* Try to handle even fatal errors */
                handle_errors(err_code);

                /* An error occured */
                result = true;
            }
        }
        return result;
    }

    //--------------------

    EventNotifier& Client::get_notify(void)
    {
        return m_Notifier; 
    }

    //--------------------
    
    void Client::toggle_random(void)
    {
        go_busy();
        mpd_run_random(conn.get_connection(),!(get_status().get_random()));
        go_idle();
    }
    
    //--------------------

    Status& Client::get_status(void)
    {
        if(conn.is_connected())
        {
            return listener->get_notify_data().get_status();
        }
    }

    //--------------------

} // END NAMESPACE 
