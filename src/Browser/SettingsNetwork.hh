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
#ifndef FREYA_SETTINGS_NETWORK_GUARD
#define FREYA_SETTINGS_NETWORK_GUARD

#include <gtkmm.h>

#include "../Config/Handler.hh"
#include "SettingsSub.hh"
#include "../Avahi/Browser.hh"

namespace Browser
{
    class Settings;
    class SettingsNetwork : public  SettingsSub
    {
        public:
            SettingsNetwork(const Glib::RefPtr<Gtk::Builder> &builder,Browser::Settings * sett);
            ~SettingsNetwork();

            void accept_new_settings(void);
            void decline_new_settings(void);
            void reset_settings(void);

        private:
            void show_avahi(void);
            void selected_callback(Glib::ustring ip,Glib::ustring hostname,Glib::ustring name, unsigned int port);
            Glib::ustring ip_name, port_name, timeout_name, autoconnect_name;

            /* Widgets */
            Avahi::Browser * handle;
            Gtk::Entry *ip;
            Gtk::SpinButton *port, *recon_timeout;
            Gtk::Button *avahi;
            Gtk::CheckButton *autoconnect;
            Gtk::MessageDialog *avahi_warning;
    };
}
#endif
