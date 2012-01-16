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
#include "Volumebutton.hh"
#include "../Utils/Utils.hh"
#include "../Notify/Notify.hh"

#define UPDATE_TIMEOUT 0.05//seconds

namespace GManager
{
    Volumebutton::Volumebutton(MPD::Client& client, const Glib::RefPtr<Gtk::Builder>& builder) :
        AbstractClientUser(client),
        m_Timerguard()
    {
        ignore_signal = false;
        BUILDER_GET(builder,"volume_button",mp_VButton);
        mp_VButton->signal_value_changed().connect(sigc::mem_fun(*this,&GManager::Volumebutton::on_user_change));
    }

// -------------------

    void Volumebutton::on_client_update(enum mpd_idle event, MPD::NotifyData& data)
    {
        if(event & (MPD_IDLE_MIXER))
        {
            /* Make sure the signal emitted by set_value() is ignored */
            ignore_signal = true;
            mp_VButton->set_value(data.get_status().get_volume() / 100.0);
            ignore_signal = false;
        }
    }

// -------------------

    void Volumebutton::on_connection_change(bool server_changed, bool is_connected)
    {
        mp_VButton->set_sensitive(is_connected);
    }

// -------------------

    void Volumebutton::do_volume_step(void)
    {
        mp_Client->set_volume(mp_VButton->get_value() * 100);
    }

// -------------------

    void Volumebutton::on_user_change(double val)
    {
        if(!ignore_signal && m_Timerguard.elapsed() > UPDATE_TIMEOUT)
        {
            Glib::signal_idle().connect_once(
                sigc::mem_fun(*this,&Volumebutton::do_volume_step),
                Glib::PRIORITY_LOW);

            m_Timerguard.reset();
        }
    }
}
