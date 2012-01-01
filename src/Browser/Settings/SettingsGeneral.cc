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
#include "SettingsGeneral.hh"
#include "Settings.hh"
#include "../../Utils/Utils.hh"

namespace Browser
{
    SettingsGeneral::SettingsGeneral(const Glib::RefPtr<Gtk::Builder> &builder,Browser::Settings * sett, GManager::Trayicon * trayptr) :
        notify("settings.libnotify.signal"),
        tray("settings.trayicon.tray"),
        timeout("settings.libnotify.timeout"),
        to_tray("settings.trayicon.totrayonclose")
    {
        this->sett=sett;
        this->trayptr=trayptr;
        BUILDER_GET(builder,"libnotify_checkbox",libnotify);
        BUILDER_GET(builder,"trayicon_checkbox",trayicon);
        BUILDER_GET(builder,"notification_timeout",notify_timeout);
        BUILDER_GET(builder,"notify_box",notify_box);
        BUILDER_GET(builder,"tray_box",tray_box);
        BUILDER_GET(builder,"totray_on_close",close_to_tray);

        libnotify->signal_toggled().connect(sigc::mem_fun(*sett,&Browser::Settings::settings_changed));
        libnotify->signal_toggled().connect(sigc::mem_fun(*this,&Browser::SettingsGeneral::on_notify_toggled));
        notify_timeout->signal_changed().connect(sigc::mem_fun(*sett,&Browser::Settings::settings_changed));

        on_notify_toggled();

        trayicon->signal_toggled().connect(sigc::mem_fun(*sett,&Browser::Settings::settings_changed));
        trayicon->signal_toggled().connect(sigc::mem_fun(*this,&Browser::SettingsGeneral::on_tray_toggled));
        close_to_tray->signal_toggled().connect(sigc::mem_fun(*sett,&Browser::Settings::settings_changed));

        on_tray_toggled();
    }


    SettingsGeneral::~SettingsGeneral(void) {}

    //----------------------------

    void SettingsGeneral::accept_new_settings(void)
    {
        bool notify_value =  libnotify->get_active();
        bool tray_value =  trayicon->get_active();
        bool to_tray_value =  close_to_tray->get_active();

        if(!tray_value)
            to_tray_value = false;

        int timeout_value =(int)notify_timeout->get_value();

        trayptr->set_visible(tray_value);

        CONFIG_SET_AS_INT(notify,notify_value?1:0);
        CONFIG_SET_AS_INT(tray,tray_value?1:0);
        CONFIG_SET_AS_INT(to_tray,to_tray_value?1:0);
        CONFIG_SET_AS_INT(timeout,timeout_value?timeout_value*1000:-1);
    }

    //----------------------------

    void SettingsGeneral::decline_new_settings(void)
    {
        int libnot, trayic, timeout_value, to_tray_value;
        libnot = CONFIG_GET_AS_INT(notify);
        trayic = CONFIG_GET_AS_INT(tray);
        to_tray_value = CONFIG_GET_AS_INT(to_tray);
        timeout_value = CONFIG_GET_AS_INT(timeout);

        if(!trayic)
            to_tray_value = 0;

        notify_timeout->set_value((double)(timeout_value==-1?0:((double)timeout_value)/1000) );
        libnotify->set_active(libnot==1);
        close_to_tray->set_active(to_tray_value==1);
        trayicon->set_active(trayic==1);
    }

    //----------------------------

    void SettingsGeneral::reset_settings(void)
    {
        int libnot, trayic, timeout_value, to_tray_value;
        libnot = CONFIG_GET_DEFAULT_AS_INT(notify);
        trayic = CONFIG_GET_DEFAULT_AS_INT(tray);
        timeout_value = CONFIG_GET_DEFAULT_AS_INT(timeout);
        to_tray_value = CONFIG_GET_DEFAULT_AS_INT(to_tray);

        if(!trayic)
            to_tray_value = 0;

        libnotify->set_active(libnot==1);
        trayicon->set_active(trayic==1);
        close_to_tray->set_active(to_tray_value==1);
        notify_timeout->set_value((double)(timeout_value==-1?0:((double)timeout_value)/1000) );
    }

    //----------------------------

    void SettingsGeneral::on_notify_toggled(void)
    {
        notify_box->set_visible(libnotify->get_active());
    }
    //----------------------------
    void SettingsGeneral::on_tray_toggled(void)
    {
        tray_box->set_visible(trayicon->get_active());
    }
}
