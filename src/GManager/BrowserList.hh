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
#ifndef FREYA_BROWSERLIST_GUARD
#define FREYA_BROWSERLIST_GUARD

#include <gtkmm.h>
#include "../Browser/AbstractBrowser.hh"
#include "../MPD/AbstractClientUser.hh"

namespace GManager
{
    /**
     * @brief List of Browsers in sidebar
     *
     * Manages a list of AbstractBrowser and switches
     * to the first browser that needs no connection on disconnect.
     * Also supports hidden Browsers (Browser::Fortune e.g.)
     */
    class BrowserList : public AbstractClientUser
    {
        public:

            BrowserList(MPD::Client& client, const Glib::RefPtr<Gtk::Builder>& builder);

            /**
             * @brief Add the browser to the list and manage it
             *
             * @param browser A user class that inherits from AbstractBrowser
             */
            void add(AbstractBrowser& browser);

            /**
             * @brief Set a specfici browser
             *
             * Note: The browser should be already added with add()
             *
             * @param browser
             */
            void set(AbstractBrowser& browser);

        private:

            void change_browser(AbstractBrowser * browser);
            void on_selection_changed(void);
            void on_client_update(enum mpd_idle type, MPD::NotifyData& data);
            void on_connection_change(bool server_changed, bool is_connected);

            /* Tree model columns: */
            class ModelColumns : public Gtk::TreeModel::ColumnRecord
            {
                public:
                    ModelColumns() { add(m_col_name); add(m_col_icon); add(m_col_browser); }
                    Gtk::TreeModelColumn<Glib::ustring> m_col_name;
                    Gtk::TreeModelColumn<Glib::RefPtr<Gdk::Pixbuf>> m_col_icon;
                    Gtk::TreeModelColumn<AbstractBrowser*> m_col_browser;
            };

            /* View */
            Gtk::TreeView * mp_PluginListview;

            /* Actual model */
            Glib::RefPtr<Gtk::ListStore> m_refTreeModel;

            /* Model layout */
            ModelColumns m_Columns;

            /* Selected data of model */
            Glib::RefPtr<Gtk::TreeSelection> m_TreeSelection;

            /* Browserlist widget, where all browser stuff is happening in */
            Gtk::Box * mp_List;
            
            /* fortune label on startup */
            Gtk::Label m_NoBrowsers;
    };
}

#endif
