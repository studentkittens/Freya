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
#include "Trayicon.hh"
#include "../Log/Writer.hh"
#include "../Config/Handler.hh"

namespace GManager
{
    Glib::ustring ui_info =
        "<ui>"
        "  <popup name='PopupMenu'>"
        "    <menuitem action='quit'/>"
        "    <separator />"
        "    <menuitem action='next'/>"
        "    <menuitem action='prev'/>"
        "    <menuitem action='stop'/>"
        "    <menuitem action='pause'/>"
        "    <separator />"
        "  </popup>"
        "</ui>";

    Trayicon::Trayicon(MPD::Client& client,Gtk::Window& main_window) :
        Gtk::StatusIcon(Gtk::Stock::INFO),
        Browser::BasePopup(NULL,ui_info),
        AbstractClientUser(client)
    {
        mp_Window = &main_window;

        set_tooltip_text("Freya Trayicon");
        set_visible(CONFIG_GET_AS_INT("settings.trayicon.tray"));

        menu_add_item(m_ActionNext,"next","Next","Play next song",Gtk::Stock::MEDIA_NEXT);
        menu_add_item(m_ActionPrev,"prev","Prev","Play prev song",Gtk::Stock::MEDIA_PREVIOUS);
        menu_add_item(m_ActionStop,"stop","Stop","Stop playing",Gtk::Stock::MEDIA_STOP);
        menu_add_item(m_ActionPause,"pause","Pause","Pause playing",Gtk::Stock::MEDIA_PLAY);
        menu_add_item(m_ActionQuit,"quit","Quit","Quit Freya fully",Gtk::Stock::QUIT);
        menu_construct("PopupMenu");

        m_ActionNext->signal_activate().connect(sigc::mem_fun(*this,&Trayicon::on_next_clicked));
        m_ActionPrev->signal_activate().connect(sigc::mem_fun(*this,&Trayicon::on_prev_clicked));
        m_ActionStop->signal_activate().connect(sigc::mem_fun(*this,&Trayicon::on_stop_clicked));
        m_ActionPause->signal_activate().connect(sigc::mem_fun(*this,&Trayicon::on_pause_clicked));
        m_ActionQuit->signal_activate().connect(sigc::mem_fun(*this,&Trayicon::on_quit_clicked));

        /* TODO This doesnt work with stalonetray.. Huh? */
        // set_from_file("ui/Trayicon.svg");
        /* Silly hack to get the right size */
        set(mp_Window->render_icon_pixbuf(Gtk::Stock::MEDIA_PLAY,Gtk::ICON_SIZE_LARGE_TOOLBAR));
    }

//-------------------------

    void Trayicon::on_popup_menu(guint button, guint32 activate_time)
    {
        mp_Popup->popup(button,activate_time);
    }

//---------------------------

    void Trayicon::on_activate(void)
    {
        mp_Window->set_visible(!mp_Window->get_visible());
    }

//---------------------------

    void Trayicon::on_next_clicked(void)
    {
        mp_Client->playback_next();
    }

//---------------------------

    void Trayicon::on_prev_clicked(void)
    {
        mp_Client->playback_prev();
    }

//---------------------------

    void Trayicon::on_stop_clicked(void)
    {
        mp_Client->playback_stop();
    }

//---------------------------

    void Trayicon::on_pause_clicked(void)
    {
        mp_Client->playback_pause();
    }

//---------------------------

    void Trayicon::on_quit_clicked(void)
    {
        Gtk::Main::quit();
    }

//---------------------------

    void Trayicon::on_connection_change(bool server_changed, bool is_connected)
    {
        m_ActionNext->set_sensitive(is_connected);
        m_ActionPrev->set_sensitive(is_connected);
        m_ActionStop->set_sensitive(is_connected);
        m_ActionPause->set_sensitive(is_connected);
    }

//---------------------------

    void Trayicon::on_client_update(enum mpd_idle event, MPD::NotifyData& data)
    {
        MPD::Status& status = data.get_status();
        if(status.get_state() == MPD_STATE_PLAY)
        {
            m_ActionPause->set_stock_id(Gtk::Stock::MEDIA_PAUSE);
            m_ActionPause->set_label("Pause");
        }
        else
        {
            m_ActionPause->set_stock_id(Gtk::Stock::MEDIA_PLAY);
            m_ActionPause->set_label("Play");
        }
    }

//---------------------------
}
