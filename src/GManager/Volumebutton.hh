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
#ifndef FREYA_VOLUMEBUTTON_GUARD
#define FREYA_VOLUMEBUTTON_GUARD

#include <gtkmm.h>
#include <gtkmm/volumebutton.h>
#include "../MPD/Client.hh"
#include "../AbstractClientUser.hh"

namespace GManager
{
    class Volumebutton : public AbstractClientUser
    {
        public:
            Volumebutton(MPD::Client& client, const Glib::RefPtr<Gtk::Builder>& builder);

        private:

            void on_client_update(enum mpd_idle type, MPD::NotifyData& data);
            void on_connection_change(bool is_connected);
            void on_user_change(double val);
            void volume_notify(int curVol);

            bool ignore_signal;
            Gtk::VolumeButton * mp_VButton;
            Glib::Timer m_Timerguard;
    };
}

#endif
