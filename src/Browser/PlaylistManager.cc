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
#include "PlaylistManager.hh"
#include "../Utils/Utils.hh"
#include "../Log/Writer.hh"

namespace Browser
{
    PlaylistManager::PlaylistManager(MPD::Client& client, Glib::RefPtr<Gtk::Builder>& builder) :
        AbstractBrowser("Playlists",true,true,Gtk::Stock::INDENT),
        AbstractClientUser(client)
    {
        BUILDER_ADD(builder,"ui/Playlists.glade");
        BUILDER_GET(builder,"playlist_treeview",mp_TreeView);

        /* Get the box and parent it to the main frame */
        Gtk::Box * playlist_box = NULL;
        BUILDER_GET(builder,"playlist_box",playlist_box);
        BUILDER_GET(builder,"playlist_add_pl",mp_AddButton);
        BUILDER_GET(builder,"playlist_delete_pl",mp_DelButton);
        BUILDER_GET(builder,"playlist_status",mp_StatusLabel);
        playlist_box->reparent(*this);

        /* Render playlist icon */
        m_PlaylistIcon = mp_TreeView->render_icon_pixbuf(Gtk::Stock::INDENT,Gtk::ICON_SIZE_BUTTON);

        /* Create the Tree model */
        m_refTreeModel = Gtk::ListStore::create(m_Columns);
        mp_TreeView->set_model(m_refTreeModel);
        m_Selection = mp_TreeView->get_selection();

        /* Add the TreeView's view columns */
        mp_TreeView->append_column("", m_Columns.m_col_icon);
        m_PlaylistTreeViewCol.set_title("Playlists");
        m_PlaylistTreeViewCol.pack_start(m_PlaylistCellRender);
        mp_TreeView->append_column(m_PlaylistTreeViewCol);
        mp_TreeView->append_column("Last modified", m_Columns.m_col_last_modfied);

        /* Directly jumping is just this line.. */
        mp_TreeView->set_search_column(1);

        /* Called once the cell needs to get the data from the model */
        m_PlaylistTreeViewCol.set_cell_data_func(m_PlaylistCellRender,
                sigc::mem_fun(*this,&PlaylistManager::on_cell_get_data));

        /* Make the CellRenderer editable, and handle its editing signals */
        m_PlaylistCellRender.property_editable() = true;

        /* Called once editing is done by the user */
        m_PlaylistCellRender.signal_edited().connect(
                sigc::mem_fun(*this,&PlaylistManager::on_cell_edited));

        /* Connect buttons in bar */
        mp_AddButton->signal_clicked().connect(
                sigc::mem_fun(*this,&PlaylistManager::on_add_clicked));
        mp_DelButton->signal_clicked().connect(
                sigc::mem_fun(*this,&PlaylistManager::on_menu_del_clicked));

        /* Cpnnect popups and row actions */
        mp_Popup = new PlaylistManagerPopup(*mp_TreeView);
        mp_Popup->get_action("pl_append").connect(
                sigc::mem_fun(*this,&PlaylistManager::on_menu_append_clicked));
        mp_Popup->get_action("pl_replace").connect(
                sigc::mem_fun(*this,&PlaylistManager::on_menu_replace_clicked));
        mp_Popup->get_action("pl_delete").connect(
                sigc::mem_fun(*this,&PlaylistManager::on_menu_del_clicked));
        mp_TreeView->signal_button_press_event().connect(
                sigc::mem_fun(*this,&PlaylistManager::on_row_double_click));

        /* Instance a new Adder dialog */
        mp_AddDialog = new PlaylistAddDialog(client,builder);

        /* Fill the actual content to the list */
        mp_Client->fill_playlists(*this);
        show_all();
    }
    
    //-----------------------------------

    /* Called when a name-cell is finished edited
     * Validates the input, and renames the mpd playlist */
    void PlaylistManager::on_cell_edited(const Glib::ustring& path_string,const Glib::ustring& new_text)
    {
        /* Get the position in the View.. */
        Gtk::TreePath path(path_string);
        Gtk::TreeModel::iterator edited_iter = m_refTreeModel->get_iter(path);
        bool is_valid = true;

        /* Lookup if Playlistname already there */
        for(Gtk::TreeModel::iterator iter = m_refTreeModel->get_iter("0"); iter; iter++)
        {
            Gtk::TreeRow row = *iter;
            if(row[m_Columns.m_col_name] == new_text && iter != edited_iter)
            {
                is_valid = false;
                break;
            }
        }

        if(!is_valid)
        {
            /* Start editing again */
            mp_TreeView->set_cursor(path, m_PlaylistTreeViewCol, m_PlaylistCellRender, true);
            mp_StatusLabel->set_text("Playlist already exist. Choose a different name.");
        }
        else
        {
            if(edited_iter)
            {
                /* Put the new value in the model */
                Gtk::TreeModel::Row row = *edited_iter;
                Glib::ustring old_name = row[m_Columns.m_col_name];
                if(old_name != new_text)
                {
                    MPD::Playlist * PList = row[m_Columns.m_col_plist];
                    PList->rename(new_text.c_str());
                }
            }
            mp_StatusLabel->set_text("");
        }
    }

    //-----------------------------------

    void PlaylistManager::on_cell_get_data(Gtk::CellRenderer*, const Gtk::TreeModel::iterator& iter)
    {
        /* Get the value from the model and show it appropriately in the view */
        if(iter)
        {
            Gtk::TreeModel::Row row = *iter;
            Glib::ustring model_value = row[m_Columns.m_col_name];
            m_PlaylistCellRender.property_text() = model_value;
        }
    }

    /* ----------------------- */

    Gtk::Widget * PlaylistManager::get_container(void)
    {
        return this;
    }

    /* ----------------------- */

    PlaylistManager::~PlaylistManager(void)
    {
        delete mp_AddDialog;
        delete mp_Popup;
    }

    /* ----------------------- */
    
    void PlaylistManager::clear(void)
    {
        for(Gtk::TreeModel::iterator iter = m_refTreeModel->get_iter("0"); iter; iter++)
        {
            MPD::Playlist * pl = (*iter)[m_Columns.m_col_plist];
            delete pl;
        }
        m_refTreeModel->clear();
    }
    
    /* ----------------------- */

    void PlaylistManager::add_item(void * pPlaylist)
    {
        g_assert(pPlaylist);
        MPD::Playlist * playlist = (MPD::Playlist*)pPlaylist;
        Gtk::TreeModel::Row row = *(m_refTreeModel->append());
        row[m_Columns.m_col_plist] = playlist;
        row[m_Columns.m_col_name]  = playlist->get_path();
        row[m_Columns.m_col_icon]  = m_PlaylistIcon;
        row[m_Columns.m_col_last_modfied] = Utils::seconds_to_timestamp(playlist->get_last_modified());
    }


    /* ----------------------- */

    void PlaylistManager::selection_helper(bool load_or_remove) 
    {
        std::vector<Gtk::TreeModel::Path> selection = m_Selection->get_selected_rows();

        /* Simple subscript is sufficient here */
        for(unsigned i = 0; i < selection.size(); i++)
        {
            Gtk::TreeModel::Path& path = selection[i];
            Gtk::TreeModel::iterator it = m_refTreeModel->get_iter(path);
            if(it)
            {
                Gtk::TreeRow row = *it;
                MPD::Playlist * PList = row[m_Columns.m_col_plist];

                if(load_or_remove)
                {
                    PList->load();
                }
                else
                {
                    PList->remove();
                }
            }
        }
    }

    /* ----------------------- */

    void PlaylistManager::on_menu_del_clicked(void)
    {
        selection_helper(false);
    }

    /* ----------------------- */

    void PlaylistManager::on_menu_append_clicked(void)
    {
        selection_helper(true);
    }

    /* ----------------------- */

    void PlaylistManager::on_menu_replace_clicked(void)
    {
        mp_Client->queue_clear();
        on_menu_append_clicked();
    }

    /* ----------------------- */

    bool PlaylistManager::on_row_double_click(GdkEventButton * event)
    {
        return false;
    }

    /* ----------------------- */

    void PlaylistManager::on_add_clicked(void)
    {
        mp_AddDialog->run();
    }

    /* ----------------------- */

    void PlaylistManager::on_client_update(enum mpd_idle event, MPD::NotifyData& data)
    {
        if(event & MPD_IDLE_STORED_PLAYLIST)
        {
            /* Update the list of playlists */
            clear();
            mp_Client->fill_playlists(*this);
        }
    }

    /* ----------------------- */

    void PlaylistManager::on_connection_change(bool is_connected)
    {}
}
