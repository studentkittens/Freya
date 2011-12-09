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
#include "Playlist.hh"

namespace MPD
{
    Playlist::Playlist(mpd_playlist& playlist)
    {
        mpc_playlist = &playlist;
    }

    Playlist::Playlist(const Playlist& copy_this)
    {
        if(copy_this.mpc_playlist != NULL)
        {
            mpc_playlist = mpd_playlist_dup(copy_this.mpc_playlist);
        }
    }

    Playlist::~Playlist(void)
    {
        if(mpc_playlist != NULL)
            mpd_playlist_free(mpc_playlist);
    }

    const char * Playlist::get_path(void)
    {
        return mpd_playlist_get_path(mpc_playlist);
    }

    time_t Playlist::get_last_modified(void)
    {
        return mpd_playlist_get_last_modified(mpc_playlist);
    }
}
