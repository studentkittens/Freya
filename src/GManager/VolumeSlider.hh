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
#ifndef FREYA_VolumeSlider_GUARD
#define FREYA_VolumeSlider_GUARD

#include <gtkmm.h>

#include "../MPD/Client.hh"
#include "../MPD/AbstractClientUser.hh"
#include "CairoSlider.hh"

namespace GManager
{
    /**
     * @brief Manages the VolumeSlider
     *
     * Updates on the mixer event, only updates every 0.05 seconds to prevent high ressource-usage.
     * Also schedules an Glib::signal_idle() event instead of executing it directly.
     */
    class VolumeSlider : public MPD::AbstractClientUser, public CairoSlider 
    {
        public:
            VolumeSlider(MPD::Client& client, const Glib::RefPtr<Gtk::Builder>& builder);

        private:

            void on_client_update(enum mpd_idle type, MPD::NotifyData& data);
            void on_connection_change(bool server_changed, bool is_connected);
            void volume_notify(int curVol);
            void do_volume_step();

        protected:

            bool on_draw(const Cairo::RefPtr<Cairo::Context>& cr);
            void on_percent_change();
    };
}

#endif
