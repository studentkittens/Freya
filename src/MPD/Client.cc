/***********************************************************
* This file is part of Freya
* - A free MPD Gtk3 MPD Client -
*
* Authors: Christopher Pahl, Christoph Piechula,
*          Eduard Schneider
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
 
    /* Go back idling, *never* forget this. */
#define GET_LAID                  \
                }                     \
                go_idle();            \
            }                         \
 
//-------------------------------

    Client::Client() {}

//-------------------------------

    Client::~Client()
    {
        disconnect();
    }

//-------------------------------

    void Client::connect()
    {
        __connect();
    }

//-------------------------------

    void Client::disconnect()
    {
        __disconnect();
    }

//-------------------------------
//-------------------------------

    bool Client::send_command(const char * command)
    {
        bool result = false;
        GET_BUSY
        {
            mpd_pair * ent = NULL;
            if(mpd_send_command(conn,command,NULL))
            {
                while((ent = mpd_recv_pair(conn)))
                {
                    /* Debugging stuff, just shown in the test_client */
                    g_printerr("%s => %s\n",ent->name,ent->value);
                    mpd_return_pair(conn,ent);
                }
            }
        }
        GET_LAID
        return result;
    }

//-------------------------------

    bool Client::playback_play()
    {
        return this->send_command("play");
    }

//-------------------------------

    bool Client::playback_stop()
    {
        return this->send_command("stop");
    }

//-------------------------------

    bool Client::playback_next()
    {
        return this->send_command("next");
    }

//-------------------------------

    bool Client::playback_prev()
    {
        return this->send_command("previous");
    }

//-------------------------------

    bool Client::playback_pause()
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

    void Client::queue_clear()
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

    void Client::fill_queue_changes(AbstractItemlist& data_model, unsigned last_version, unsigned& first_pos)
    {
        bool is_first = true;
        GET_BUSY
        {
            if(mpd_send_queue_changes_meta(conn,last_version) != FALSE)
            {
                mpd_song * ent = NULL;
                while((ent = mpd_recv_song(conn)))
                {
                    Song * new_song = new Song(*ent);
                    if(is_first)
                    {
                        first_pos = new_song->get_pos();
                        is_first = false;
                    }
                    data_model.add_item(new_song);
                }
            }

            if(is_first)
            {
                first_pos = get_status()->get_queue_length();
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

    void Client::fill_outputs(AbstractItemlist& data_model)
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

    void Client::fill_filelist(AbstractItemlist& data_model, const char * path)
    {
        GET_BUSY
        {
            if(mpd_send_list_meta(conn, (path) ? path : "/") != FALSE)
            {
                mpd_entity * ent = NULL;
                while((ent = mpd_recv_entity(conn)))
                {
                    switch(mpd_entity_get_type(ent))
                    {
                        /* Making duplicates is silly, but that's how mpd_entity_get_song/dir works */
                    case MPD_ENTITY_TYPE_DIRECTORY:
                    {
                        mpd_directory * dir = (mpd_directory*)mpd_entity_get_directory(ent);
                        if(dir != NULL)
                        {
                            mpd_directory * dup_dir = mpd_directory_dup(dir);
                            data_model.add_item(new MPD::Directory(*dup_dir));
                        }
                        break;
                    }
                    case MPD_ENTITY_TYPE_SONG:
                    {
                        mpd_song * song = (mpd_song*)mpd_entity_get_song(ent);
                        if(song != NULL)
                        {
                            mpd_song * dup_song = mpd_song_dup(song);
                            data_model.add_item(new MPD::Song(*dup_song));
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
        }
        GET_LAID
    }

//--------------------

//--------------------

    void Client::toggle_random()
    {
        GET_BUSY
        {
            mpd_run_random(conn,!(get_status()->get_random()));
        }
        GET_LAID
    }

//--------------------

    void Client::toggle_consume()
    {
        GET_BUSY
        {
            mpd_run_consume(conn,!(get_status()->get_consume()));
        }
        GET_LAID
    }

//--------------------

    void Client::toggle_repeat()
    {
        GET_BUSY
        {
            mpd_run_repeat(conn,!(get_status()->get_repeat()));
        }
        GET_LAID
    }

//--------------------

    void Client::toggle_single()
    {
        GET_BUSY
        {
            mpd_run_single(conn,!(get_status()->get_single()));
        }
        GET_LAID
    }

//--------------------

    void Client::play_song_at_id(unsigned song_id)
    {
        GET_BUSY
        {
            mpd_run_play_id(conn,song_id);
        }
        GET_LAID
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

    void Client::playback_crossfade(unsigned seconds)
    {
        GET_BUSY
        {
            mpd_run_crossfade(conn,seconds);
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

    void Client::playlist_save(const char * name)
    {
        GET_BUSY
        {
            mpd_run_save(conn,name);
        }
        GET_LAID
    }
    
//--------------------

    bool Client::ping()
    {
        bool retv = false;
        GET_BUSY
        {
            if(mpd_send_command(conn,"ping",NULL))
                retv = mpd_response_finish(conn);
        }
        GET_LAID
        
        return retv;
    }

} // END NAMESPACE
