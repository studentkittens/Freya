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
#ifndef FREYA_SETTINGS_GUARD
#define FREYA_SETTINGS_GUARD

#include <gtkmm.h>
#include <vector>

#include "SettingsPlayback.hh"
#include "SettingsNetwork.hh"
#include "SettingsGeneral.hh"
#include "SettingsOutputs.hh"
#include "AbstractSettings.hh"

#include "../AbstractBrowser.hh"
#include "../../Config/Handler.hh"
#include "../../GManager/Trayicon.hh"

using namespace std;

namespace Browser
{
    /**
     * @brief The Settingsbrowser shown in the sidebar
     */
    class Settings : public AbstractBrowser
    {
    public:
        Settings(MPD::Client& client, const Glib::RefPtr<Gtk::Builder> &builder, GManager::Trayicon * tray);
        ~Settings();

        /**
         * @brief Implemented from AbstractBrowser
         *
         * @return
         */
        Gtk::Widget* get_container();
        /**
         * @brief Called when saving the Config (makes ok/cancel insensitive)
         */
        void settings_changed();

    private:
        void on_button_ok();
        void on_button_cancel();
        void on_button_reset();
        vector<AbstractSettings*> sub_sections;

        /* Widgets */
        Gtk::Button *ok_button, *cancel_button, *reset_button;
        Gtk::Box *settings_main;

    };
}

#endif
