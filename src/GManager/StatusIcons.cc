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
#include "StatusIcons.hh"
#include "../Utils/Utils.hh"

namespace GManager
{
    Statusicons::Statusicons(MPD::Client& client, const Glib::RefPtr<Gtk::Builder>& builder) :
        AbstractClientUser(client)
    {
        ignore_updates = false;

        BUILDER_GET(builder,"icon_random",mp_Random);
        mp_Random->signal_clicked().connect(sigc::mem_fun(*this,&Statusicons::on_clicked_random));

        BUILDER_GET(builder,"icon_single",mp_Single);
        mp_Single->signal_clicked().connect(sigc::mem_fun(*this,&Statusicons::on_clicked_single));

        BUILDER_GET(builder,"icon_repeat",mp_Repeat);
        mp_Repeat->signal_clicked().connect(sigc::mem_fun(*this,&Statusicons::on_clicked_repeat));

        BUILDER_GET(builder,"icon_consume",mp_Consume);
        mp_Consume->signal_clicked().connect(sigc::mem_fun(*this,&Statusicons::on_clicked_consume));
    }

    void Statusicons::on_connection_change(bool server_changed, bool is_connected)
    {
        mp_Random->set_sensitive(is_connected);
        mp_Single->set_sensitive(is_connected);
        mp_Repeat->set_sensitive(is_connected);
        mp_Consume->set_sensitive(is_connected);
    }

    void Statusicons::on_client_update(enum mpd_idle type, MPD::NotifyData& data)
    {
        if(type & (MPD_IDLE_OPTIONS))
        {
            ignore_updates = true;
            MPD::Status& status = data.get_status();
            mp_Consume->set_active(status.get_consume()); 
            mp_Random->set_active(status.get_random()); 
            mp_Repeat->set_active(status.get_repeat()); 
            mp_Single->set_active(status.get_single()); 
            ignore_updates = false;
        }
    }

    void Statusicons::on_clicked_random(void)
    {
        if(!ignore_updates) mp_Client->toggle_random(); 
    }

    void Statusicons::on_clicked_single(void)
    {
        if(!ignore_updates) mp_Client->toggle_single(); 
    }

    void Statusicons::on_clicked_consume(void)
    {
        if(!ignore_updates) mp_Client->toggle_consume(); 
    }

    void Statusicons::on_clicked_repeat(void)
    {
        if(!ignore_updates) mp_Client->toggle_repeat(); 
    }
}
