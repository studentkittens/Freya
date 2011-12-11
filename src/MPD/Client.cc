 /***********************************************************
* This file is part of Freya 
* - A free MPD Gtk3 MPD Client -
* 
* Authors: Christopher Pahl, Christoph Piechula,
*          Eduard Schneider, Marc Tigges
*
* Copyright (C) [2011-2012]
* Hosted at: https://github.com/studentkittens/Freya
*
*              __..--''``---....___   _..._    __
*    /// //_.-'    .-/";  `        ``<._  ``.''_ `. / // /
*   ///_.-' _..--.'_                        `( ) ) // //
*   / (_..-' // (< _     ;_..__               ; `' / ///
*    / // // //  `-._,_)' // / ``--...____..-' /// / //  
*  Ascii-Art by Felix Lee <flee@cse.psu.edu>
*
* Freya is free software: you can redistribute it and/or modify
* it under the terms of the GNU General Public License as published by
* the Free Software Foundation, either version 3 of the License, or
* (at your option) any later version.
*
* Freya is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
* GNU General Public License for more details.
*
* You should have received a copy of the GNU General Public License
* along with Freya. If not, see <http://www.gnu.org/licenses/>.
**************************************************************/
#include "Client.hh"
#include "../Log/Writer.hh"
#include "../Config/Handler.hh"

#include "Playlist.hh"
#include "Directory.hh"
#include "AudioOutput.hh"

namespace MPD
{
    /* Go into active mode */
    #define GET_BUSY                     \
            if(m_Conn.is_connected())    \
            {                            \
                go_busy();               \
                mpd_connection * conn =  \
                m_Conn.get_connection(); \
                if(conn != NULL) {       \

    /* Go back idling, *never* forget this :P */                
    #define GET_LAID                  \
                }                     \
                go_idle();            \
            }                         \

    //-------------------------------

    Client::Client() : m_ListBegun(false), m_Notifier()
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
        m_Conn.signal_error().connect(
                sigc::mem_fun(*this,&Client::handle_errors));

        if(m_Conn.connect())
        {
            m_Conn.clear_error();

            mp_Listener = new MPD::Listener(&m_Notifier,m_Conn);
            go_idle();
            m_ConnNotifer.emit(true);
            mp_Listener->force_update();
        }
    }

    //-------------------------------

    void Client::disconnect(void)
    {
        if(m_Conn.is_connected())
        {
            m_Conn.clear_error();
            if(mp_Listener)
            {
                if(mp_Listener != NULL)
                {
                    mp_Listener->leave();
                    delete mp_Listener;
                }

            }
            m_Conn.disconnect();
            m_ConnNotifer.emit(false);
        }
    }


    //-------------------------------

    void Client::begin(void)
    {
        go_busy();
        m_ListBegun = true;
        mpd_command_list_begin(m_Conn.get_connection(),true);
    }

    //-------------------------------

    void Client::commit(void)
    {
        mpd_connection * conn = m_Conn.get_connection();
        mpd_command_list_end(conn);
        mpd_response_finish(conn);
        m_ListBegun = false;
        go_idle();
    }

    //-------------------------------
    //-------------------------------

    bool Client::send_command(const char * command)
    {
        bool result = false;
        GET_BUSY
        {
            mpd_pair * ent = NULL;
            mpd_send_command(conn,command,NULL);

            while((ent = mpd_recv_pair(conn)))
            {
                /* Debugging stuff, just shown in the test_client */
                g_printerr("%s => %s\n",ent->name,ent->value);
                mpd_return_pair(conn,ent);
            }
        }
        GET_LAID
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
            mpd_connection * conn = m_Conn.get_connection();
            if(m_ListBegun)
            {
                mpd_send_add(conn,path);
            }
            else
            {
                GET_BUSY
                {
                    mpd_run_add(conn,path);
                }
                GET_LAID
            }
        }
    }

    //-------------------------------

    void Client::queue_delete(unsigned id)
    {
        mpd_connection * conn = m_Conn.get_connection();
        if(m_ListBegun)
        {
            mpd_send_delete_id(conn,id);
        }
        else
        {
            GET_BUSY
            {
                mpd_run_delete_id(conn,id);
            }
            GET_LAID
        }
    }

    //-------------------------------

    void Client::queue_delete_range(unsigned pos_start, unsigned pos_end)
    {
        GET_BUSY
        {
            mpd_run_delete_range(conn,pos_start,pos_end);
        }
        GET_LAID
    }

    //-------------------------------

    void Client::queue_clear(void)
    {
        GET_BUSY
        {
            mpd_run_clear(conn);
        }
        GET_LAID
    }

    //-------------------------------

    unsigned Client::database_update(const char * path)
    {
        unsigned id = 0;
        GET_BUSY
        {
            id = mpd_run_update(conn,path);
        }
        GET_LAID

        return id;
    }

    //-------------------------------

    unsigned Client::database_rescan(const char * path)
    {
        unsigned id = 0;
        GET_BUSY
        {
             id = mpd_run_rescan(conn,path);
        }
        GET_LAID

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
        GET_BUSY
        {
            if(mpd_send_list_queue_meta(conn) != FALSE)
            {
                mpd_song * ent = NULL;
                while((ent = mpd_recv_song(conn)))
                {
                    data_model.add_item(new Song(*ent));
                }
            }
        }
        GET_LAID
    }

    //-------------------------------

    void Client::fill_playlists(AbstractItemlist& data_model)
    {
        GET_BUSY
        {
            if(mpd_send_list_playlists(conn) != FALSE)
            {
                mpd_playlist * ent = NULL;
                while((ent = mpd_recv_playlist(conn)))
                {
                    data_model.add_item(new Playlist(*this,*ent));
                }
            }
        }
        GET_LAID
    }

    //-------------------------------
    
    void Client::fill_ouputs(AbstractItemlist& data_model)
    {
        GET_BUSY
        {
            if(mpd_send_outputs(conn) != FALSE) 
            {
                mpd_output * ent = NULL;
                while((ent = mpd_recv_output(conn)))
                {
                    data_model.add_item(new AudioOutput(*this,*ent));
                }
            }
        }
        GET_LAID
    }
    
    //-------------------------------

    void Client::fill_filelist(AbstractFilebrowser& data_model, const char * path)
    {
        GET_BUSY
        {
            if(mpd_send_list_meta(conn, path) != FALSE)
            {
                mpd_entity * ent = NULL;
                while((ent = mpd_recv_entity(conn)))
                {
                    switch(mpd_entity_get_type(ent))
                    {
                        case MPD_ENTITY_TYPE_DIRECTORY:
                            {
                                mpd_directory * dir = (mpd_directory*)mpd_entity_get_directory(ent);
                                if(dir != NULL)
                                {
                                    data_model.add_directory(new MPD::Directory(*dir));
                                }
                                break;
                            }
                        case MPD_ENTITY_TYPE_SONG:
                            {
                                mpd_song * song = (mpd_song*)mpd_entity_get_song(ent);
                                if(song != NULL)
                                {
                                    data_model.add_song_file(new MPD::Song(*song));
                                }
                                break;
                            }
                        case MPD_ENTITY_TYPE_PLAYLIST:
                        case MPD_ENTITY_TYPE_UNKNOWN:
                        default:
                            mpd_entity_free(ent);
                            break;
                    }
                }
            }
        }
        GET_LAID
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

    void Client::handle_errors(bool is_fatal, mpd_error err)
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
                    int interval = CONFIG_GET_AS_INT("settings.connection.reconnectinterval") * 1000;
                    Glib::signal_timeout().connect(
                            sigc::mem_fun(*this, &Client::timeout_reconnect),
                            interval,G_PRIORITY_DEFAULT_IDLE);

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

    //--------------------

    EventNotifier& Client::signal_client_update(void)
    {
        return m_Notifier; 
    }

    //--------------------

    void Client::toggle_random(void)
    {
        GET_BUSY
        {
             mpd_run_random(conn,!(get_status()->get_random()));
        }
        GET_LAID
    }

    //--------------------

    void Client::toggle_consume(void)
    {
        GET_BUSY
        {
             mpd_run_consume(conn,!(get_status()->get_consume()));
        }
        GET_LAID
    }

    //--------------------

    void Client::toggle_repeat(void)
    {
        GET_BUSY
        {
             mpd_run_repeat(conn,!(get_status()->get_repeat()));
        }
        GET_LAID
    }

    //--------------------

    void Client::toggle_single(void)
    {
        GET_BUSY
        {
             mpd_run_single(conn,!(get_status()->get_single()));
        }
        GET_LAID
    }

    void Client::play_song_at_id(unsigned song_id)
    {
        GET_BUSY
        {
             mpd_run_play_id(conn,song_id);
        }
        GET_LAID
    }

    //--------------------

    Status * Client::get_status(void)
    {
        if(m_Conn.is_connected())
        {
            return &(mp_Listener->signal_client_update_data().get_status());
        }
        Warning("get_status() while being disconnected");

        return NULL;
    }

    //--------------------

    void Client::force_update(void)
    {
        if(m_Conn.is_connected())
            mp_Listener->force_update();
    }

    //--------------------

    void Client::playback_seek(unsigned song_id, unsigned abs_time)
    {
        GET_BUSY
        {
            mpd_run_seek_id(conn,song_id,abs_time);
        }
        GET_LAID
    }

    //--------------------

    void Client::set_volume(unsigned vol)
    {
        GET_BUSY
        {
             mpd_run_set_volume(conn,vol);
        }
        GET_LAID
    }

    //--------------------

    ConnectionNotifier& Client::signal_connection_change(void)
    {
        return m_ConnNotifer;
    }

    //--------------------

    void Client::playlist_save(const char * name) 
    {
        GET_BUSY
        {
            mpd_run_save(conn,name);
        }
        GET_LAID
    }

} // END NAMESPACE 
