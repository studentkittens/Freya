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
#ifndef FREYA_SETTINGS_NETWORK_GUARD
#define FREYA_SETTINGS_NETWORK_GUARD

#include "../../Config/Handler.hh"
#include "AbstractSettings.hh"

#include <gtkmm.h>

namespace Browser
{
class Settings;

/**
 * @brief Network Settings Tab.
 */
class SettingsNetwork : public AbstractSettings
{
public:
    SettingsNetwork(Glib::RefPtr<Gtk::Builder> &builder,Browser::Settings * sett);
    ~SettingsNetwork();

    void accept_new_settings();
    void decline_new_settings();
    void reset_settings();

private:
    void show_avahi(Browser::Settings * sett);
    void selected_callback(Glib::ustring ip,Glib::ustring hostname,Glib::ustring name, unsigned int port);
    Glib::ustring ip_name, port_name, timeout_name, autoconnect_name;

    /* Widgets */
    Gtk::Entry *ip;
    Gtk::SpinButton *port, *recon_timeout;
    Gtk::Button *avahi;
    Gtk::CheckButton *autoconnect;
    Gtk::MessageDialog *avahi_warning;
};
}
#endif
