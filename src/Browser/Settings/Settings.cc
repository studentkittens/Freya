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
#include "Settings.hh"
#include "../../Utils/Utils.hh"
#include "../../Log/Writer.hh"
#include "../../Notify/Notify.hh"
#include "../../MPD/AbstractItemlist.hh"
namespace Browser
{
    Settings::Settings(MPD::Client& client, const Glib::RefPtr<Gtk::Builder> &builder, GManager::Trayicon * tray):
        AbstractBrowser("Settings",true,false,Gtk::Stock::PREFERENCES)
    {
        BUILDER_ADD(builder,"ui/Settings.glade");
        BUILDER_GET(builder,"ok_button",ok_button);
        BUILDER_GET(builder,"cancel_button",cancel_button);
        BUILDER_GET(builder,"reset_button",reset_button);
        BUILDER_GET(builder,"settings_main",settings_main);

        sub_sections.push_back(new SettingsNetwork(builder, this));
        sub_sections.push_back(new SettingsPlayback(client,builder,this));
        sub_sections.push_back(new SettingsGeneral(builder, this, tray));
        sub_sections.push_back(new SettingsOutputs(client,builder,this));


        ok_button->signal_clicked().connect(sigc::mem_fun(*this,&Settings::on_button_ok));
        cancel_button->signal_clicked().connect(sigc::mem_fun(*this,&Settings::on_button_cancel));
        reset_button->signal_clicked().connect(sigc::mem_fun(*this,&Settings::on_button_reset));

        on_button_cancel();

        ok_button->set_sensitive(false);
        cancel_button->set_sensitive(false);

    }
//---------------------------

    Settings::~Settings(void)
    {
        for(unsigned int i=0; i<sub_sections.size(); i++)
            delete sub_sections[i];
    }

//---------------------------

    void Settings::on_button_ok(void)
    {
        for(unsigned int i=0; i< sub_sections.size(); i++)
        {
            sub_sections[i]->accept_new_settings();
        }
        CONFIG_SAVE_NOW();
        ok_button->set_sensitive(false);
        cancel_button->set_sensitive(false);
        Notify::Notify::instance().re_init();
    }
//---------------------------
    void Settings::on_button_cancel(void)
    {
        for(unsigned int i=0; i< sub_sections.size(); i++)
        {
            sub_sections[i]->decline_new_settings();
        }
        ok_button->set_sensitive(false);
        cancel_button->set_sensitive(false);
    }
//---------------------------
    Gtk::Widget* Settings::get_container(void)
    {
        return settings_main;
    }
//---------------------------
    void Settings::on_button_reset(void)
    {
        for(unsigned int i=0; i< sub_sections.size(); i++)
        {
            sub_sections[i]->reset_settings();
        }
    }
//--------------------------
    void Settings::settings_changed(void)
    {
        ok_button->set_sensitive(true);
        cancel_button->set_sensitive(true);
    }
}
