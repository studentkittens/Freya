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
#ifndef FREYA_SETTINGS_GENERAL_GUARD
#define FREYA_SETTINGS_GENERAL_GUARD

#include "../../Config/Handler.hh"
#include "../../GManager/Trayicon.hh"
#include "AbstractSettings.hh"

namespace Browser
{
    /* Prototype */
    class Settings;

    /**
     * @brief General Settings Tab.
     */
    class SettingsGeneral : public AbstractSettings
    {
    public:
        SettingsGeneral(const Glib::RefPtr<Gtk::Builder> &builder,Browser::Settings * sett, GManager::Trayicon *trayptr);
        ~SettingsGeneral();

        void accept_new_settings();
        void decline_new_settings();
        void reset_settings();

    private:
        void on_notify_toggled();
        void on_tray_toggled();
        GManager::Trayicon * trayptr;
        Browser::Settings * sett;
        Glib::ustring notify,tray,timeout, to_tray;
        /* Widgets */
        Gtk::CheckButton *libnotify, *trayicon, *close_to_tray;
        Gtk::SpinButton *notify_timeout;
        Gtk::Box *notify_box, *tray_box;
    };
}
#endif
