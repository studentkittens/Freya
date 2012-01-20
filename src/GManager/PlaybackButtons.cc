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
#include "PlaybackButtons.hh"
#include "../Log/Writer.hh"
#include "../Utils/Utils.hh"

namespace GManager
{
    PlaybackButtons::PlaybackButtons(MPD::Client& instance, const Glib::RefPtr<Gtk::Builder>& builder) :
        AbstractClientUser(instance),
        play_icon(Gtk::Stock::MEDIA_PLAY,Gtk::ICON_SIZE_SMALL_TOOLBAR),
        pause_icon(Gtk::Stock::MEDIA_PAUSE,Gtk::ICON_SIZE_SMALL_TOOLBAR)
    {
        BUILDER_GET(builder,"stop_button",stop_button);
        BUILDER_GET(builder,"pause_button",pause_button);
        BUILDER_GET(builder,"prev_button",prev_button);
        BUILDER_GET(builder,"next_button",next_button);

        stop_button->signal_clicked().connect(sigc::mem_fun(*this,&PlaybackButtons::on_button_stop));
        pause_button->signal_clicked().connect(sigc::mem_fun(*this,&PlaybackButtons::on_button_pause));
        prev_button->signal_clicked().connect(sigc::mem_fun(*this,&PlaybackButtons::on_button_prev));
        next_button->signal_clicked().connect(sigc::mem_fun(*this,&PlaybackButtons::on_button_next));
    }

//----------------------------

    void PlaybackButtons::on_button_stop()
    {
        mp_Client->playback_stop();
    }

//----------------------------

    void PlaybackButtons::on_button_pause()
    {
        mp_Client->playback_pause();
    }

//----------------------------

    void PlaybackButtons::on_button_prev()
    {
        mp_Client->playback_prev();
    }

//----------------------------

    void PlaybackButtons::on_button_next()
    {
        mp_Client->playback_next();
    }

//----------------------------

    void PlaybackButtons::on_client_update(enum mpd_idle event, MPD::NotifyData& data)
    {
        if(event & MPD_IDLE_PLAYER)
        {
            pause_button->set_image((data.get_status().get_state() == MPD_STATE_PLAY) ? pause_icon : play_icon);
        }
    }

//----------------------------

    void PlaybackButtons::on_connection_change(bool server_changed, bool is_connected)
    {
        stop_button->set_sensitive(is_connected);
        prev_button->set_sensitive(is_connected);
        next_button->set_sensitive(is_connected);
        pause_button->set_sensitive(is_connected);
    }
}
