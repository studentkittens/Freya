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
#ifndef PLAYLISTMANAGER_LUYIHGVL
#define PLAYLISTMANAGER_LUYIHGVL

#include <gtkmm.h>
#include "../AbstractItemlist.hh"
#include "../AbstractClientUser.hh"
#include "../MPD/Client.hh"
#include "../MPD/Playlist.hh"

#include "AbstractBrowser.hh"
#include "PlaylistManagerPopup.hh"
#include "PlaylistAddDialog.hh"

namespace Browser 
{
    class PlaylistManager : 
        public Gtk::Frame, 
        public AbstractBrowser, 
        public AbstractItemlist,
        public AbstractClientUser
    {
        public:
            PlaylistManager(MPD::Client& client, Glib::RefPtr<Gtk::Builder>& builder);
            virtual ~PlaylistManager();

            /**
             * @brief Inherited from AbstractBrowser
             *
             * @return a pointer to the widget containing the playlist
             */
            Gtk::Widget * get_container(void);

        private:

            /* Menu Popup */
            void on_menu_append_clicked(void);
            void on_menu_replace_clicked(void);
            void on_menu_del_clicked(void);
            void selection_helper(bool load_or_remove);

            /* Other */
            bool on_row_double_click(GdkEventButton * event);

            /* Clear list (frees memory) */
            void clear(void);

            /* Implemented from AbstractItemlist */
            void add_item(void * pPlaylist);

            /* Implemented from AbstractClientUser */
            void on_client_update(enum mpd_idle event, MPD::NotifyData& data);
            void on_connection_change(bool is_connected);

            void on_cell_edited(const Glib::ustring& path_string,const Glib::ustring& new_text);
            void on_cell_get_data(Gtk::CellRenderer*, const Gtk::TreeModel::iterator& iter);

            /* Tree model columns: */
            class ModelColumns : public Gtk::TreeModel::ColumnRecord
            {
                public:

                    ModelColumns()
                    { add(m_col_icon);
                      add(m_col_plist);
                      add(m_col_name);
                      add(m_col_last_modfied); }

                    Gtk::TreeModelColumn<Glib::RefPtr<Gdk::Pixbuf>> m_col_icon;
                    Gtk::TreeModelColumn<MPD::Playlist*> m_col_plist;
                    Gtk::TreeModelColumn<Glib::ustring> m_col_name;
                    Gtk::TreeModelColumn<Glib::ustring> m_col_last_modfied;
            };

            /* Treeview related */
            ModelColumns m_Columns;

            Gtk::TreeView * mp_TreeView;
            Glib::RefPtr<Gtk::ListStore> m_refTreeModel;
            Glib::RefPtr<Gtk::TreeSelection> m_Selection;

            /* We need to validate renames of playlists
             * Therefore we render the cell on our own
             * Taken from: 
             * http://developer.gnome.org/gtkmm-tutorial/stable/sec-treeview-examples.html.de
             */
            Gtk::CellRendererText m_PlaylistCellRender;
            Gtk::TreeView::Column m_PlaylistTreeViewCol;

            /* Control buttons */
            Gtk::Button * mp_DelButton; 

            /* Status label */
            Gtk::Label * mp_StatusLabel;

            /* Popup menu */
            PlaylistManagerPopup * mp_Popup;

            /* Playlist Icon */
            Glib::RefPtr<Gdk::Pixbuf> m_PlaylistIcon;

            /* Add dialog */
            PlaylistAddDialog * mp_AddDialog;
    };
}

#endif /* end of include guard: PLAYLISTMANAGER_LUYIHGVL */
