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
#ifndef FREYA_STATUSBAR_GUARD
#define FREYA_STATUSBAR_GUARD

#include "../ui_includes.hh"

#include "../MPD/Client.hh"
#include "../MPD/AbstractClientUser.hh"
#include "Heartbeat.hh"

namespace GManager
{
/**
 * @brief Manager for the statusbar
 *
 * Updates the statusbar every 0.5 seconds
 */
class Statusbar : public MPD::AbstractClientUser
{
public:

    Statusbar(Heartbeat& tproxy, MPD::Client& client, const Glib::RefPtr<Gtk::Builder>& builder);
    ~Statusbar();

private:
    void on_client_update(enum mpd_idle, MPD::NotifyData& data);
    void on_heartbeat(double time);
    void format_time(unsigned time, char buffer[]);
    void do_update_message(MPD::NotifyData& data);
    void on_connection_change(bool server_changed, bool is_connected);

    MPD::NotifyData * mp_Lastdata;
    Gtk::Label * m_Statusbar;
    Heartbeat * mp_Heartbeat;
    gchar * mp_Message;
};
}
#endif
