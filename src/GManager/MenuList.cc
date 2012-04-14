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
#include "MenuList.hh"

#include "../Log/Writer.hh"
#include "../Utils/Utils.hh"
#include "../../config.h"

namespace GManager
{
MenuList::MenuList(MPD::Client &client, Glib::RefPtr<Gtk::Builder> &builder) :
    AbstractClientUser(client),
    running(false)
{
    BUILDER_GET(builder,"menu_item_connect", menu_connect);
    BUILDER_GET(builder,"menu_item_disconnect", menu_disconnect);
    BUILDER_GET(builder,"menu_item_quit", menu_quit);
    BUILDER_GET(builder,"menu_item_play", menu_play);
    BUILDER_GET(builder,"menu_item_stop", menu_stop);
    BUILDER_GET(builder,"menu_item_prev", menu_prev);
    BUILDER_GET(builder,"menu_item_next", menu_next);
    BUILDER_GET(builder,"menu_mode_repeat", menu_repeat);
    BUILDER_GET(builder,"menu_mode_single", menu_single);
    BUILDER_GET(builder,"menu_mode_random", menu_random);
    BUILDER_GET(builder,"menu_mode_consume", menu_consume);
    BUILDER_GET(builder,"menu_about",menu_about);
    BUILDER_GET(builder,"playback_menuitem",menu_playback);
    BUILDER_ADD(builder,"ui/About.glade");
    BUILDER_GET_NO_MANAGE(builder,"about_main",window_about);

    /*
     * Fetch about dialog preferrably from memory
     */
    window_about->set_logo(Utils::pixbuf_internal_fetch("ui/gfx/Freya_about.jpg",-1,-1));

    /*
     * Update actual version
     */
    Glib::ustring version_string = Glib::ustring("Version ") +
        (FREYA_VERSION_MAJOR"."
         FREYA_VERSION_MINOR"."
         FREYA_VERSION_MICRO" "
         FREYA_VERSION_NAME);

    window_about->set_version(version_string);

    menu_connect->signal_activate().connect(
            sigc::mem_fun(*this,&MenuList::on_menu_connect));
    menu_disconnect->signal_activate().connect(
            sigc::mem_fun(*this,&MenuList::on_menu_disconnect));
    menu_quit->signal_activate().connect(
            sigc::mem_fun(*this,&MenuList::on_menu_quit));
    menu_play->signal_activate().connect(
            sigc::mem_fun(*this,&MenuList::on_menu_play));
    menu_stop->signal_activate().connect(
            sigc::mem_fun(*this,&MenuList::on_menu_stop));
    menu_prev->signal_activate().connect(
            sigc::mem_fun(*this,&MenuList::on_menu_prev));
    menu_next->signal_activate().connect(
            sigc::mem_fun(*this,&MenuList::on_menu_next));
    menu_random->signal_toggled().connect(
            sigc::mem_fun(*this,&MenuList::on_menu_random));
    menu_repeat->signal_toggled().connect(
            sigc::mem_fun(*this,&MenuList::on_menu_repeat));
    menu_single->signal_toggled().connect(
            sigc::mem_fun(*this,&MenuList::on_menu_single));
    menu_consume->signal_toggled().connect(
            sigc::mem_fun(*this,&MenuList::on_menu_consume));
    menu_about->signal_activate().connect(
            sigc::mem_fun(*this,&MenuList::on_menu_about));
}

//-----------------------------
MenuList::~MenuList()
{
    delete window_about;
}
//-----------------------------
void MenuList::on_menu_connect()
{
    mp_Client->connect();
}
//-----------------------------
void MenuList::on_menu_disconnect()
{
    mp_Client->disconnect();
}
//-----------------------------
void MenuList::on_menu_quit()
{
    Gtk::Main::quit();
}
//-----------------------------
void MenuList::on_menu_play()
{
    mp_Client->playback_pause();
}
//-----------------------------
void MenuList::on_menu_stop()
{
    mp_Client->playback_stop();
}
//-----------------------------
void MenuList::on_menu_prev()
{
    mp_Client->playback_prev();
}
//-----------------------------
void MenuList::on_menu_next()
{
    mp_Client->playback_next();
}

//-----------------------------

void MenuList::on_connection_change(bool server_changed, bool is_connected)
{
    menu_connect->set_sensitive(!is_connected);
    menu_disconnect->set_sensitive(is_connected);
    menu_playback->set_sensitive(is_connected);
}

//-----------------------------

void MenuList::on_client_update(enum mpd_idle event, MPD::NotifyData &data)
{
    if((event & MPD_IDLE_OPTIONS) && !running)
    {
        running = true;
        MPD::Status &stat = data.get_status();
        menu_random->set_active(stat.get_random());
        menu_repeat->set_active(stat.get_repeat());
        menu_single->set_active(stat.get_single());
        menu_consume->set_active(stat.get_consume());
        running = false;
    }
}

//-----------------------------

void MenuList::on_menu_random()
{
    if(!running) mp_Client->toggle_random();
}
//-----------------------------
void MenuList::on_menu_repeat()
{
    if(!running) mp_Client->toggle_repeat();
}
//-----------------------------
void MenuList::on_menu_single()
{
    if(!running) mp_Client->toggle_single();
}
//-----------------------------
void MenuList::on_menu_consume()
{
    if(!running) mp_Client->toggle_consume();
}
//-----------------------------
void MenuList::on_menu_about()
{
    window_about->run();
    window_about->hide();
}
//-----------------------------
}
