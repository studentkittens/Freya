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
#ifndef FREYA_QUEUE_H
#define FREYA_QUEUE_H

#include <gtkmm.h>
#include "../../MPD/AbstractItemlist.hh"
#include "../../MPD/AbstractClientUser.hh"
#include "../../MPD/Client.hh"

#include "QueuePopup.hh"
#include "QueueMerger.hh"
#include "QueueModelColumns.hh"
#include "PlaylistAddDialog.hh"
#include "../AbstractBrowser.hh"

namespace Browser 
{
    /**
     * @brief Shows a list of songs in the current playlist
     *
     * It does not offer you any public methods.
     * The fetching and updating is done by QueueMerger.
     */
    class Queue : public AbstractBrowser, public MPD::AbstractClientUser
    {
        public:
            Queue(MPD::Client& client, Glib::RefPtr<Gtk::Builder>& builder);
            virtual ~Queue();

            /**
             * @brief Inherited from AbstractBrowser
             *
             * @return a pointer to the widget containing the playlist
             */
            Gtk::Widget * get_container(void);

        private:

            /* Init */
            void configure_columns(void);
            void configure_signals(void);

            /* Implemtend from AbstractItemlist */
            void add_item(void * pSong);

            /* Util */
            void merge_changes(MPD::Song * pSong);

            /* Implemented from AbstractClientUser */
            void on_client_update(enum mpd_idle event, MPD::NotifyData& data);
            void on_connection_change(bool server_changed, bool is_connected);

            /* Menuhandling */
            void on_menu_clear_clicked(void);
            void on_menu_remove_clicked(void);
            void on_menu_add_as_pl_clicked(void);

            /* Other */
            void on_row_activated(const Gtk::TreeModel::Path& path, Gtk::TreeViewColumn* column);
            bool on_filter_row_visible(const Gtk::TreeModel::const_iterator& iter);
            void on_entry_activate(void);
            void on_entry_clear_icon(Gtk::EntryIconPosition icon_pos, const GdkEventButton* event);
            bool on_key_press_handler(GdkEventKey * event);

            /*----------------------*/
            /*----------------------*/
            /*----------------------*/

            Glib::ustring m_FilterText;

            /* Treeview related */
            QueueModelColumns m_Columns;

            /* View of the list */
            Gtk::TreeView * mp_TreeView;

            /* Actual data */
            Glib::RefPtr<Gtk::ListStore> m_refTreeModel;

            /* Filtered data */
            Glib::RefPtr<Gtk::TreeModelFilter> m_refTreeModelFilter;

            /* Selected data */
            Glib::RefPtr<Gtk::TreeSelection> m_TreeSelection;

            /* Popup */
            QueuePopup * mp_Popup;
            
            /* other widgets */
            Gtk::Entry * mp_Entry;
            Gtk::Box * mp_QueueBox;
            PlaylistAddDialog * mp_AddDialog;

            /* Current Song */
            MPD::Song * mp_CurrentSong;

            /* Handles updating the queue */
            QueueMerger * mp_Merger;
    };
}
#endif //FREYA_QUEUE_H
