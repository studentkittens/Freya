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
#ifndef FREYA_TIMESLIDE_GUARD
#define FREYA_TIMESLIDE_GUARD

#include <gtkmm.h>
#include "Heartbeat.hh"
#include "../MPD/AbstractClientUser.hh"

namespace GManager
{
    /**
     * @brief Manager for the Timeslide in the topbar
     *
     * Updates the time every 500ms according to the Heartbeat.
     */
    class Timeslide : public MPD::AbstractClientUser
    {
    public:
        Timeslide(Heartbeat& tproxy, MPD::Client& client, const Glib::RefPtr<Gtk::Builder>& builder);

    private:
        void tick(double time);
        void on_client_update(enum mpd_idle event, MPD::NotifyData& data);
        void on_connection_change(bool server_changed, bool is_connected);
        void on_user_action(void);
        void do_scroll(void);

        unsigned current_song_id;
        bool ignore_signal;
        Gtk::Scale * m_Timeslide;
        GManager::Heartbeat * mp_Heartbeat;

        Glib::Timer m_Timeguard;
    };
}
#endif
