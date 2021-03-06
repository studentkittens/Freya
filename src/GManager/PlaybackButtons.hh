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
#ifndef FREYA_PLAYBACKBUTTONS_GUARD
#define FREYA_PLAYBACKBUTTONS_GUARD

#include "../ui_includes.hh"
#include "../MPD/Client.hh"
#include "../MPD/AbstractClientUser.hh"

namespace GManager
{
/**
 * @brief Manages the Playbackbuttons
 *
 * Does nothing more than catching signals, and changing symbols.
 */
class PlaybackButtons : public MPD::AbstractClientUser
{
public:
    PlaybackButtons(MPD::Client& client, const Glib::RefPtr<Gtk::Builder>& builder);

private:
    /* Client Signals */
    void on_client_update(enum mpd_idle event, MPD::NotifyData& data);
    void on_connection_change(bool server_changed, bool is_connected);

    /* GTK Signals */
    void on_button_stop();
    void on_button_pause();
    void on_button_next();
    void on_button_prev();

    /* Widgets */
    Gtk::Button *stop_button, *pause_button, *prev_button, *next_button;
    Gtk::Image play_icon, pause_icon;
};
}

#endif
