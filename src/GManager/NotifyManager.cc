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
#include "NotifyManager.hh"

namespace GManager
{
NotifyManager::NotifyManager(MPD::Client& client) :
    AbstractClientUser(client)
{}

////////////////////////////////

void NotifyManager::on_client_update(enum mpd_idle event, MPD::NotifyData& data)
{
    if(event & MPD_IDLE_PLAYER)
    {
        MPD::Song * current_song = data.get_song();
        if(current_song != NULL)
        {
            MPD::Status& status = data.get_status();
            if((status.get_state() == MPD_STATE_PLAY))
                NOTIFY_STOCK_ICON("media-playback-start");
            else if((status.get_state() == MPD_STATE_STOP))
                NOTIFY_STOCK_ICON("media-playback-stop");
            else if((status.get_state() == MPD_STATE_PAUSE))
                NOTIFY_STOCK_ICON("media-playback-pause");
            NOTIFY_SEND(current_song->song_format("${title} (Track ${track})",false),current_song->song_format("by ${artist} on ${album} (${date})",true));
        }
    }
}

////////////////////////////////

void NotifyManager::on_connection_change(bool server_changed, bool is_connected)
{
    NOTIFY_EXTRA();
    if(is_connected)
    {
        NOTIFY_STOCK_ICON("network-idle");
        NOTIFY_SEND("","Freya conntected!");
    }
    else
    {
        NOTIFY_STOCK_ICON("network-error");
        NOTIFY_SEND("","Freya disconnected!");
    }
}

////////////////////////////////

}
