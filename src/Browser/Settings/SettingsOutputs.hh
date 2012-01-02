/***********************************************************
* This file is part of Freya
* - A free MPD Gtk3 MPD Client -
*
* Authors: Christopher Pahl, Christoph Piechula,
*          Eduard Schneider, Marc Tigges
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
#ifndef FREYA_SETTINGS_OUTPUTS_GUARD
#define FREYA_SETTINGS_OUTPUTS_GUARD

#include <gtkmm.h>

#include "AbstractSettings.hh"
#include "OutputsModelColumns.hh"
#include "../../MPD/AbstractItemlist.hh"
#include "../../MPD/AbstractClientUser.hh"
#include "../../MPD/Client.hh"
#include "../../Utils/Utils.hh"

namespace Browser
{
    class Settings;

    /**
     * @brief Outputlist Tab
     */
    class SettingsOutputs : public AbstractSettings, public MPD::AbstractItemlist, public MPD::AbstractClientUser
    {
    public:
        SettingsOutputs(MPD::Client &client,const Glib::RefPtr<Gtk::Builder> &builder, Browser::Settings * sett);
        ~SettingsOutputs();

        void accept_new_settings(void);
        void decline_new_settings(void);
        void reset_settings(void);
        void add_item(MPD::AbstractComposite *item);

    protected:
        void on_client_update(enum mpd_idle event, MPD::NotifyData& data);
        void on_connection_change(bool,bool);
        void on_toggle(const Glib::ustring& path);
        bool on_select(const Glib::RefPtr<Gtk::TreeModel>& model,const Gtk::TreeModel::Path& path, bool);
        void clear(void);

    private:
        Glib::RefPtr<Gtk::ListStore> treeModel;
        Gtk::TreeView * treeViewPtr;
        OutputsModelColumns treeColumns;
        MPD::Client* client;
        Settings *sett;
        bool running;
    };


}




#endif
