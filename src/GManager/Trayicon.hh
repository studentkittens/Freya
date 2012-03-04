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
#ifndef FREYA_TRAYICON_GUARD
#define FREYA_TRAYICON_GUARD

#include "../ui_includes.hh"
#include "../MPD/Client.hh"
#include "../Browser/BasePopup.hh"
#include "../MPD/AbstractClientUser.hh"

namespace GManager
{
    /**
     * @brief Manager for the trayicon
     *
     * It is deriving from Gtk::StatusIcon, that's why you may call show()/hide() functions here.
     */
    class Trayicon : public Gtk::StatusIcon, public Browser::BasePopup, public MPD::AbstractClientUser
    {
    public:
        Trayicon(MPD::Client& client,Gtk::Window& main_window);

    private:

        void on_activate();
        void on_popup_menu (guint button, guint32 activate_time);

        void on_connection_change(bool server_changed, bool is_connected);
        void on_client_update(enum mpd_idle event, MPD::NotifyData& data);

        void on_next_clicked();
        void on_prev_clicked();
        void on_stop_clicked();
        void on_pause_clicked();
        void on_quit_clicked();

        Glib::RefPtr<Gtk::Action> m_ActionNext;
        Glib::RefPtr<Gtk::Action> m_ActionPrev;
        Glib::RefPtr<Gtk::Action> m_ActionStop;
        Glib::RefPtr<Gtk::Action> m_ActionPause;
        Glib::RefPtr<Gtk::Action> m_ActionQuit;
        Gtk::Window * mp_Window;
    };
}
#endif /* end of include guard: FREYA_TRAYICON_GUARD */
