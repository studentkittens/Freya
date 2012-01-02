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
#ifndef FREYA_STATUSICONS_GUARD
#define FREYA_STATUSICONS_GUARD

#include <gtkmm.h>
#include "../MPD/Client.hh"
#include "../MPD/AbstractClientUser.hh"

namespace GManager
{
    /**
     * @brief Manager for the status icons in the down sidebar
     *
     * Toggles/updates random, consume, repeat, single.
     */
    class Statusicons : public MPD::AbstractClientUser
    {
    public:
        Statusicons(MPD::Client& client, const Glib::RefPtr<Gtk::Builder>& builder);

    private:
        void on_client_update(enum mpd_idle, MPD::NotifyData& data);
        void on_connection_change(bool server_changed, bool is_connected);

        void on_clicked_random(void);
        void on_clicked_single(void);
        void on_clicked_consume(void);
        void on_clicked_repeat(void);
        void on_conn_change(bool is_connected);

        /* Widgets */
        Gtk::ToggleButton *mp_Random, * mp_Single, * mp_Consume, * mp_Repeat;

        /* set_active() emits a signal, this would cause infinite loops of updating,
         * ignore signals while recv. updates from client therefore. */
        bool ignore_updates;
    };
}

#endif
