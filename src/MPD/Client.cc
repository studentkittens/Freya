#include "Client.hh"
#include "../Log/Writer.hh"
#include "../Config/Handler.hh"
#include "Playlist.hh"
#include "Directory.hh"

#define ACTIVITY_SECTION(CODE)  \
    if(m_Conn.is_connected()) { \
        go_busy();              \
        CODE                    \
        go_idle();              \
    }                           \

namespace MPD
{
    //-------------------------------

    Client::Client() : m_Conn(), m_Notifier()
    {
        if(CONFIG_GET_AS_INT("settings.connection.autoconnect"))
        {
            connect();
        }
    }

    //-------------------------------

    Client::~Client()
    {
        disconnect();
    }

    //-------------------------------

    void Client::connect(void)
    {
        if(m_Conn.connect())
        {
            Info("Creating Listener");
            listener = new Listener(&m_Notifier,m_Conn);
            go_idle();
            m_ConnNotifer.emit(true);
            listener->force_update();
        }
    }

    //-------------------------------

    void Client::disconnect(void)
    {
        if(listener)
        {
            if(listener != NULL)
                delete listener;

            m_Conn.disconnect();
            m_ConnNotifer.emit(false);
        }
    }

    //-------------------------------

    bool Client::is_connected(void)
    {
        return m_Conn.is_connected();
    }

    //-------------------------------

    void Client::go_idle(void)
    {
        check_error();
        if(listener->is_idling() == false)
        {
            listener->enter();
        }
    }

    //-------------------------------

    void Client::go_busy(void)
    {
        if(listener->is_idling() == true)
        {
            listener->leave();
        }
        check_error();
    }

    //-------------------------------
    //-------------------------------

    bool Client::send_command(const char * command)
    {
        bool result = false;
        if(command != NULL && m_Conn.is_connected())
        {
            /* Go into active mode */
            go_busy();

            /* Send the command - throw away response */
            mpd_connection * mpd_conn = m_Conn.get_connection();
            mpd_send_command(mpd_conn,command,NULL);

            mpd_pair * ent = NULL;
            while((ent = mpd_recv_pair(mpd_conn)))
            {
                /* Debugging stuff, just shown in the test_client */
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

    void Client::queue_add(const char * path)
    {
        if(path != NULL)
        {
            ACTIVITY_SECTION
                (
                 mpd_connection * conn = m_Conn.get_connection();
                 mpd_run_add(conn,path);
                )
        }
    }

    //-------------------------------
    
    void Client::queue_clear(void)
    {
        ACTIVITY_SECTION
            (
             mpd_run_clear(m_Conn.get_connection());
            )
    }
    
    //-------------------------------

    unsigned Client::database_update(const char * path)
    {
        unsigned id = 0;
        if(path != NULL)
        {
            ACTIVITY_SECTION
                (
                 mpd_connection * conn = m_Conn.get_connection();
                 id = mpd_run_update(conn,path);
                )
        }
        return id;
    }

    //-------------------------------

    bool Client::playback_pause(void)
    {
        if(m_Conn.is_connected())
        {
            if(get_status()->get_state() != MPD_STATE_STOP)
                return this->send_command("pause");
            else
                return this->send_command("play");
        }
        return false;
    }

    //-------------------------------

    void Client::fill_queue(AbstractItemlist& data_model)
    {
        if(m_Conn.is_connected())
        {
            go_busy();

            mpd_connection * mpd_conn = m_Conn.get_connection();
            if(mpd_conn && mpd_send_list_queue_meta(mpd_conn) != FALSE)
            {
                mpd_song * ent = NULL;
                while((ent = mpd_recv_song(mpd_conn)))
                {
                    data_model.add_item(new Song(*ent));
                }
            }
            go_idle();
        }
    }

    //-------------------------------

    void Client::fill_playlists(AbstractItemlist& data_model)
    {
        if(m_Conn.is_connected())
        {
            go_busy();

            mpd_connection * mpd_conn = m_Conn.get_connection();
            if(mpd_conn && mpd_send_list_playlists(mpd_conn) != FALSE)
            {
                mpd_playlist * ent = NULL;
                while((ent = mpd_recv_playlist(mpd_conn)))
                {
                    data_model.add_item(new Playlist(*ent));
                }
            }
            
            go_idle();
        }
    }

    //-------------------------------

    void Client::fill_filelist(AbstractFilebrowser& data_model, const char * path)
    {
        if(m_Conn.is_connected())
        {
            go_busy();

            mpd_connection * mpd_conn = m_Conn.get_connection();
            if(mpd_conn && mpd_send_list_meta(mpd_conn, path) != FALSE)
            {
                mpd_entity * ent = NULL;
                while((ent = mpd_recv_entity(mpd_conn)))
                {
                    switch(mpd_entity_get_type(ent))
                    {
                        case MPD_ENTITY_TYPE_DIRECTORY:
                            {
                                mpd_directory * dir = (mpd_directory*)mpd_entity_get_directory(ent);
                                if(dir != NULL)
                                {
                                    data_model.add_directory(new Directory(*dir));
                                }
                                break;
                            }
                        case MPD_ENTITY_TYPE_SONG:
                            {
                                mpd_song * song = (mpd_song*)mpd_entity_get_song(ent);
                                if(song != NULL)
                                {
                                    data_model.add_song_file(new Song(*song));
                                }
                                break;
                            }
                        case MPD_ENTITY_TYPE_PLAYLIST:
                        case MPD_ENTITY_TYPE_UNKNOWN:
                        default:
                            break;
                    }
                    mpd_entity_free(ent);
                }
            }
            go_idle();
        }
    }

    //-------------------------------

    gboolean Client::timeout_reconnect(void)
    {
        connect();

        gboolean retv = m_Conn.is_connected();
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
        if(m_Conn.is_connected())
        {
            /* Check for errors at this connection and log them */
            mpd_connection * mpd_conn = m_Conn.get_connection();

            /* Get the errorcode */
            enum mpd_error err_code = mpd_connection_get_error(mpd_conn);
            if(err_code != MPD_ERROR_SUCCESS)
            {
                if(err_code == MPD_ERROR_SERVER)
                    Warning("ServerErrorId #%d: ",mpd_connection_get_server_error(mpd_conn));
                else
                    Warning("Error #%d: ",err_code);

                Warning("%s",mpd_connection_get_error_message(mpd_conn));

                /* Clear non fatal errors */
                m_Conn.clear_error();

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
        ACTIVITY_SECTION
            (
             mpd_run_random(m_Conn.get_connection(),!(get_status()->get_random()));
            )
    }

    //--------------------

    void Client::toggle_consume(void)
    {
        ACTIVITY_SECTION
            (
             mpd_run_consume(m_Conn.get_connection(),!(get_status()->get_consume()));
            )
    }

    //--------------------

    void Client::toggle_repeat(void)
    {
        ACTIVITY_SECTION
            (
             mpd_run_repeat(m_Conn.get_connection(),!(get_status()->get_repeat()));
            )
    }

    //--------------------

    void Client::toggle_single(void)
    {
        ACTIVITY_SECTION
            (
             mpd_run_single(m_Conn.get_connection(),!(get_status()->get_single()));
            )
    }

    void Client::play_song_at_id(unsigned song_id)
    {
        ACTIVITY_SECTION
            (
             mpd_run_play_id(m_Conn.get_connection(),song_id);
            )
    }

    //--------------------

    Status * Client::get_status(void)
    {
        if(m_Conn.is_connected())
        {
            return &(listener->get_notify_data().get_status());
        }
        Warning("get_status() while being disconnected");
        return NULL;
    }

    //--------------------

    void Client::force_update(void)
    {
        if(m_Conn.is_connected())
        {
            listener->force_update();
        }
    }

    //--------------------

    void Client::playback_seek(unsigned song_id, unsigned abs_time)
    {
        ACTIVITY_SECTION
            (
             mpd_run_seek_id(m_Conn.get_connection(),song_id,abs_time);
            )
    }

    //--------------------

    void Client::set_volume(unsigned vol)
    {
        ACTIVITY_SECTION
            (
             mpd_run_set_volume(m_Conn.get_connection(),vol);
            )
    }

    //--------------------

    ConnectionNotifier& Client::signal_connection_change(void)
    {
        return m_ConnNotifer;
    }

    //--------------------

    void Client::playlist_remove(const char * name)
    {
        if(name != NULL)
        {
            ACTIVITY_SECTION
                (
                 mpd_run_rm(m_Conn.get_connection(),name);
                )
        }
    }

    //--------------------


} // END NAMESPACE 
