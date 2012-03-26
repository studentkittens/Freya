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
#include "SettingsNetwork.hh"
#include "Settings.hh"
#include "../../Utils/Utils.hh"
#include "../../Log/Writer.hh"
#include "../../Notify/Notify.hh"

namespace Browser
{
    SettingsNetwork::SettingsNetwork(Glib::RefPtr<Gtk::Builder> &builder, Browser::Settings * sett) :
        ip_name("settings.connection.host"),
        port_name("settings.connection.port"),
        timeout_name("settings.connection.reconnectinterval"),
        autoconnect_name("settings.connection.autoconnect")
    {
        BUILDER_GET(builder,"ip_textfield",ip);
        BUILDER_GET(builder,"port_spinbutton",port);
        BUILDER_GET(builder,"reconnect_spinbutton",recon_timeout);
        BUILDER_GET(builder,"autoconnect_checkbox",autoconnect);

        Gtk::Expander * avahi_expander;
        Gtk::ScrolledWindow * avahi_scrl_window;

        BUILDER_ADD(builder,"ui/AvahiBrowser.glade");
        BUILDER_GET(builder,"avahi_expander",avahi_expander);
        BUILDER_GET(builder,"avahi_scrolledwindow",avahi_scrl_window);

        avahi_expander->add(*avahi_scrl_window);

        avahi_expander->property_expanded().signal_changed().connect(
                sigc::mem_fun(*this,&SettingsNetwork::show_avahi)
                );

        ip->signal_changed().connect(
                sigc::mem_fun(*sett,&Browser::Settings::settings_changed)
                );
        port->signal_value_changed().connect(
                sigc::mem_fun(*sett,&Browser::Settings::settings_changed)
                );
        recon_timeout->signal_value_changed().connect(
                sigc::mem_fun(*sett,&Browser::Settings::settings_changed)
                );
        autoconnect->signal_toggled().connect(
                sigc::mem_fun(*sett,&Browser::Settings::settings_changed)
                );
    }

    //----------------------------

    SettingsNetwork::~SettingsNetwork()
    {
        delete avahi_warning;
    }

    //----------------------------

    void SettingsNetwork::accept_new_settings()
    {
        Glib::ustring ip_value;
        int port_value, timeout_value;
        bool autoconnect_value;

        ip_value = ip->get_text();
        if(ip_value.size() == 0)
        {
            Info("Empty Server-IP entered. Falling back to previous IP");
            ip->set_text(CONFIG_GET(ip_name));
            ip_value = CONFIG_GET(ip_name);
        }
        port_value = port->get_value_as_int();
        timeout_value = recon_timeout->get_value_as_int();
        autoconnect_value = autoconnect->get_active();

        CONFIG_SET(ip_name,ip_value);
        CONFIG_SET_AS_INT(port_name,port_value);
        CONFIG_SET_AS_INT(timeout_name,timeout_value);
        CONFIG_SET_AS_INT(autoconnect_name,autoconnect_value ? 1 : 0);
    }

    //----------------------------

    void SettingsNetwork::decline_new_settings()
    {
        ip->set_text(CONFIG_GET(ip_name));
        port->set_value((double)CONFIG_GET_AS_INT(port_name));
        recon_timeout->set_value((double)CONFIG_GET_AS_INT(timeout_name));
        autoconnect->set_active(CONFIG_GET_AS_INT(autoconnect_name));
    }

    //----------------------------
    void SettingsNetwork::show_avahi()
    {
        if(avahi_handle.is_connected())
        {
            avahi_handle.signal_selection_done().connect(
                    sigc::mem_fun(*this,&Browser::SettingsNetwork::selected_callback)
                    );

            avahi_handle.get_window().show();
        }
        else
        {
            avahi_warning->run();
            avahi_warning->hide();
        }
    }
    //----------------------------

    void SettingsNetwork::selected_callback(Glib::ustring ip,Glib::ustring hostname,Glib::ustring name, unsigned int port)
    {
        this->ip->set_text(ip);
        this->port->set_value((double)port);
    }
    //----------------------------
    void SettingsNetwork::reset_settings()
    {
        ip->set_text(CONFIG_GET_DEFAULT(ip_name));
        port->set_value((double)CONFIG_GET_DEFAULT_AS_INT(port_name));
        recon_timeout->set_value((double)CONFIG_GET_DEFAULT_AS_INT(timeout_name));
        autoconnect->set_active(CONFIG_GET_DEFAULT_AS_INT(autoconnect_name));
    }
}
