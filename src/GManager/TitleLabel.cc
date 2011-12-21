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
#include "TitleLabel.hh"
#include "../Utils/Utils.hh"
#include "../Notify/Notify.hh"
namespace GManager
{
    TitleLabel::TitleLabel(MPD::Client& client, const Glib::RefPtr<Gtk::Builder>& builder)
        : AbstractClientUser(client)
    {
        BUILDER_GET(builder,"title_label",mp_TitleLabel);
        BUILDER_GET(builder,"artist_album_label",mp_ArtistAlbumLabel);
        BUILDER_GET(builder,"next_song_artist",mp_NextSongArtistLabel);
        BUILDER_GET(builder,"next_song_title",mp_NextSongTitleLabel);
    }

    //----------------
    
    void TitleLabel::stash_next_title(void)
    {
        mp_NextSongArtistLabel->set_markup("<small>No next Artist</small>");
        mp_NextSongTitleLabel->set_markup("<small>No next Title</small>");
    }

    //----------------

    void TitleLabel::update_next_song_widget(MPD::NotifyData& data)
    {
        MPD::Song * current_song = data.get_next_song(); 
        if(current_song != NULL)
        {

            mp_NextSongArtistLabel->set_markup(current_song->song_format("<small>${title}</small>"));
            mp_NextSongTitleLabel->set_markup(current_song->song_format("<small>${artist}</small>"));

        }
        else
        {
            stash_next_title();
        }
    }

    //----------------

    void TitleLabel::on_connection_change(bool is_connected)
    {
        if(!is_connected)
        {
            mp_TitleLabel->set_markup("<b>You do not seem to be connected :-(</b>");
            mp_ArtistAlbumLabel->set_markup("<small>Adjust your settings and try File->Connect</small>");
            stash_next_title();
        }
    }

    //----------------

    void TitleLabel::on_client_update(enum mpd_idle event, MPD::NotifyData& data)
    {
        if(event & (MPD_IDLE_PLAYER))
        {
            MPD::Song * current_song = data.get_song();
            if(current_song != NULL)
            {

                mp_TitleLabel->set_markup(current_song->song_format("<b>${title}</b> (Track ${track})")); 
                mp_ArtistAlbumLabel->set_markup(current_song->song_format("<small><span weight='light'><i>by</i></span> ${artist} <span weight='light'><i>on</i></span> ${album} (${date})</small>")); 

            }
            else
            {
                mp_TitleLabel->set_markup("<b>Not Playing</b>"); 
                mp_ArtistAlbumLabel->set_markup("<small>Select a new Song</small>"); 
            }
        }

        if(event & (MPD_IDLE_PLAYER|MPD_IDLE_OPTIONS))
        {
            update_next_song_widget(data);
        }
    }
}
