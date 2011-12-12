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
#include "SettingsPlayback.hh"
#include "Settings.hh"
#include "../MPD/Client.hh"
#include "../Utils/Utils.hh"

namespace Browser
{
    SettingsPlayback::SettingsPlayback(MPD::Client& client, const Glib::RefPtr<Gtk::Builder> &builder,Browser::Settings * sett) :
        AbstractClientUser(client),
        crossfade_name("settings.playback.crossfade"),
        stoponexit_name("settings.playback.stoponexit")
    {
        BUILDER_GET(builder,"crossfade_spinbutton",crossfade);
        BUILDER_GET(builder,"stoponexit_checkbox",stoponexit);
        crossfade->signal_value_changed().connect(sigc::mem_fun(*sett,&Browser::Settings::settings_changed));
        stoponexit->signal_toggled().connect(sigc::mem_fun(*sett,&Browser::Settings::settings_changed));
    }


    SettingsPlayback::~SettingsPlayback(void) {}

    //----------------------------

    void SettingsPlayback::accept_new_settings(void)
    {
        unsigned crossfade_value = crossfade->get_value_as_int();
        bool stoponexit_value =  stoponexit->get_active();
        
        mp_Client->playback_crossfade(crossfade_value);
        CONFIG_SET_AS_INT(stoponexit_name,stoponexit_value?1:0);
    }

    //----------------------------

    void SettingsPlayback::decline_new_settings(void)
    {
        crossfade->set_value(CONFIG_GET_AS_INT(crossfade_name));
        stoponexit->set_active(CONFIG_GET_AS_INT(stoponexit_name)==1);
    }

    //----------------------------

    void SettingsPlayback::reset_settings(void)
    {
        crossfade->set_value(CONFIG_GET_DEFAULT_AS_INT(crossfade_name));
        stoponexit->set_active(CONFIG_GET_DEFAULT_AS_INT(stoponexit_name)==1);
    }
    
    //----------------------------
    
    void SettingsPlayback::on_client_update(mpd_idle event, MPD::NotifyData& data)
    {
        if(event & MPD_IDLE_OPTIONS)
        {
            crossfade->set_value(data.get_status().get_crossfade());
        }
    }
    
    //----------------------------
    
    void SettingsPlayback::on_connection_change(bool is_connected)
    {
        crossfade->set_sensitive(is_connected);
    }
    
    //----------------------------
}
