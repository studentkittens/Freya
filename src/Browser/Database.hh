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
#ifndef FREYA_DATABASE_FOGI85CP
#define FREYA_DATABASE_FOGI85CP

#include <gtkmm.h>
#include "../MPD/AbstractItemlist.hh"
#include "../MPD/AbstractClientUser.hh"
#include "../MPD/Client.hh"
#include "../MPD/Directory.hh"

#include "DatabaseCache.hh"
#include "DatabasePopup.hh"
#include "AbstractBrowser.hh"

namespace Browser
{
    /* Does not inherig from frame this time */
    class Database : public AbstractBrowser, public AbstractFilebrowser, public AbstractClientUser 
    {
        public:
            Database(MPD::Client& client, Glib::RefPtr<Gtk::Builder>& builder);
            virtual ~Database();

            Gtk::Widget * get_container(void);
            void add_directory(MPD::Directory * pDir);
            void add_song_file(MPD::Song * pSong);

            void on_menu_db_add_clicked(void);
            void on_menu_db_add_all_clicked(void);
            void on_menu_db_update_clicked(void);
            void on_menu_db_rescan_clicked(void);
            void on_menu_db_replace_clicked(void);

        private:

            /* GUI Signals */
            void on_item_activated(const Gtk::TreeModel::Path& path);
            void on_home_button_clicked(void);
            void on_search_entry_activated(void);
            bool on_button_press_event(GdkEventButton* event);
            bool on_key_press_handler(GdkEventKey * event);

            /* Client Signals */
            void on_client_update(enum mpd_idle event, MPD::NotifyData& data);
            void on_connection_change(bool server_changed, bool is_connected);
           
            /* Logic */ 
            void add_item(const char * path, bool is_file);
            void set_current_path(const char * path);
            void go_one_up(void);
            void focus_item_starting_with(const char * prefix);

            class ModelColumns : public Gtk::TreeModel::ColumnRecord
            {
                public:
                    ModelColumns()
                    { add(m_col_path);
                      add(m_col_name);
                      add(m_col_icon);
                      add(m_col_is_file);
                    }

                    Gtk::TreeModelColumn<Glib::ustring> m_col_name;
                    Gtk::TreeModelColumn<Glib::ustring> m_col_path;
                    Gtk::TreeModelColumn<Glib::RefPtr<Gdk::Pixbuf>> m_col_icon;
                    Gtk::TreeModelColumn<bool> m_col_is_file;
            };

            // MEMBERS //

            /* Actual widgets */
            Gtk::IconView * mp_IView;
            Gtk::Box * mp_ParentBox;
            Gtk::Button * mp_HomeButton, * mp_DirUpButton;
            Gtk::Label * mp_StatusLabel;
            Glib::RefPtr<Gdk::Pixbuf> m_FileIcon, m_DirIcon;
            Gtk::Entry * mp_SearchEntry;

            /* Models behind */
            ModelColumns m_Columns;
            Glib::RefPtr<Gtk::ListStore> m_DirStore;

            /* The current path shown (NULL for root) */
            std::string mp_Path;

            /* Popup menu */
            DatabasePopup * mp_Popup;

            /* A local memcache of the db files */
            DatabaseCache m_Cache;

    };
}

#endif /* end of include guard: DATABASE_FOGI85CP */
