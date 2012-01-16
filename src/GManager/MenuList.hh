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
#ifndef FREYA_MENULIST_GUARD
#define FREYA_MENULIST_GUARD

#include <gtkmm.h>
#include "../MPD/Client.hh"
#include "../MPD/AbstractClientUser.hh"
#include "../Notify/Notify.hh"

namespace GManager
{
    /**
     * @brief The Manager for the Topmenus
     *
     * Also defines quite some keybindings, but no releveant public methods.
     */
    class MenuList : public MPD::AbstractClientUser
    {
    public:

        MenuList(MPD::Client &client, const Glib::RefPtr<Gtk::Builder> &builder);
        ~MenuList();

    private:

        void on_connection_change(bool server_changed, bool is_connected);
        void on_client_update(enum mpd_idle event, MPD::NotifyData &data);

        void on_menu_connect(void);
        void on_menu_disconnect(void);
        void on_menu_quit(void);

        void on_menu_play(void);
        void on_menu_stop(void);
        void on_menu_prev(void);
        void on_menu_next(void);

        void on_menu_random(void);
        void on_menu_repeat(void);
        void on_menu_single(void);
        void on_menu_consume(void);

        void on_menu_about(void);

        bool running;

        /* Widgets */
        Gtk::MenuItem *menu_connect, *menu_disconnect, *menu_quit,
            *menu_play, *menu_stop, *menu_prev, *menu_next,
            *menu_playback,  *menu_about;

        Gtk::CheckMenuItem *menu_random, *menu_repeat, *menu_single, *menu_consume;
        Gtk::AboutDialog * window_about;
    };

}



#endif
