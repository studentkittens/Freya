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
#ifndef FREYA_SETTINGS_PLAYBACK_GUARD
#define FREYA_SETTINGS_PLAYBACK_GUARD

#include "../../ui_includes.hh"
#include "../../Config/Handler.hh"
#include "../../MPD/Client.hh"
#include "../../MPD/AbstractClientUser.hh"
#include "AbstractSettings.hh"

namespace Browser
{
    class Settings;

    /**
     * @brief Playback Settings Tab
     */
    class SettingsPlayback : public AbstractSettings, public MPD::AbstractClientUser
    {
    public:
        SettingsPlayback(MPD::Client& client, const Glib::RefPtr<Gtk::Builder> &builder, Browser::Settings * sett);
        ~SettingsPlayback();

        void accept_new_settings();
        void decline_new_settings();
        void reset_settings();

    private:

        void on_client_update(mpd_idle event, MPD::NotifyData& data);
        void on_connection_change(bool server_changed, bool is_connected);

        Glib::ustring name, stoponexit_name;
        /* Widgets */
        Gtk::SpinButton *crossfade;
        Gtk::CheckButton *stoponexit;
    };
}
#endif
