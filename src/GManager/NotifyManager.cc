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
#include "NotifyManager.hh"

namespace GManager
{
    NotifyManager::NotifyManager(MPD::Client& client) :
        AbstractClientUser(client)
    {
        /* Everything by AbstractClientUser already */
    }

    // ------------------------------------

    void NotifyManager::on_client_update(enum mpd_idle event, MPD::NotifyData& data)
    { 
        if(event & MPD_IDLE_PLAYER)
        {
            MPD::Song * current_song = data.get_song();
            if(current_song != NULL)
            {
                MPD::Status& status = data.get_status();
                char * title_notify = g_markup_printf_escaped("%s (Track %s)",
                        current_song->get_tag(MPD_TAG_TITLE,0),
                        current_song->get_tag(MPD_TAG_TRACK,0)
                        );
                char * artist_notify = g_markup_printf_escaped("by %s on %s (%s)",
                        current_song->get_tag(MPD_TAG_ARTIST,0),
                        current_song->get_tag(MPD_TAG_ALBUM,0),
                        current_song->get_tag(MPD_TAG_DATE,0)
                        );

                if((status.get_state() == MPD_STATE_PLAY))
                    NOTIFY_STOCK_ICON("media-playback-start");
                else if((status.get_state() == MPD_STATE_STOP))
                    NOTIFY_STOCK_ICON("media-playback-stop");
                else if((status.get_state() == MPD_STATE_PAUSE))
                    NOTIFY_STOCK_ICON("media-playback-pause");

                NOTIFY_SEND(title_notify,artist_notify);

                g_free(title_notify);
                g_free(artist_notify);
            }
        }
    }

    // ------------------------------------

    void NotifyManager::on_connection_change(bool is_connected)
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

    // ------------------------------------

}
