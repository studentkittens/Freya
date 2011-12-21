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
#include "Queue.hh"
#include "../Log/Writer.hh"
#include "../Utils/Utils.hh"
#include <vector>

using namespace std;

namespace Browser
{
    Queue::Queue(MPD::Client& client, Glib::RefPtr<Gtk::Builder>& builder) :
        AbstractBrowser("Queue",true,true,Gtk::Stock::ZOOM_FIT),
        AbstractClientUser(client),
        m_FilterText(""),
        m_PlaylistVersion(0)
    {
        
        BUILDER_ADD(builder,"ui/Queue.glade");
        BUILDER_GET(builder,"queue_treeview",mp_TreeView);
        BUILDER_GET(builder,"queue_search_entry",mp_Entry);
        BUILDER_GET(builder,"queue_box",mp_QueueBox);

        mp_Entry->signal_activate().connect(
                sigc::mem_fun(*this,&Queue::on_entry_activate));
        mp_Entry->signal_icon_press().connect(
                sigc::mem_fun(*this, &Queue::on_entry_clear_icon));

        //Create the Tree model:
        m_refTreeModel = Gtk::ListStore::create(m_Columns);
        m_refTreeModelFilter = Gtk::TreeModelFilter::create(m_refTreeModel);
        m_refTreeModelFilter->set_visible_func(
                sigc::mem_fun(*this,&Queue::on_filter_row_visible));

        mp_TreeView->set_model(m_refTreeModelFilter);

        /* Add the TreeView's view columns: */
        /* Useful for debugging purpose */
        //mp_TreeView->append_column("ID", m_Columns.m_col_id);
        mp_TreeView->append_column("Artist", m_Columns.m_col_artist);
        mp_TreeView->append_column("Album", m_Columns.m_col_album);
        mp_TreeView->append_column("Title", m_Columns.m_col_title);

        mp_TreeView->set_rules_hint(true);
        mp_TreeView->set_rubber_banding(true);
        mp_TreeView->set_search_column(m_Columns.m_col_artist);
        mp_TreeView->set_search_entry(*mp_Entry);

        vector<Gtk::TreeView::Column*> v_Columns = mp_TreeView->get_columns();
        for(unsigned it = 0; it < v_Columns.size(); it++)
        {
            Gtk::TreeView::Column * pColumn = v_Columns.at(it);
            if(pColumn != NULL)
            {
                pColumn->set_reorderable();
                pColumn->set_expand(true);
                pColumn->set_resizable(true);
                pColumn->set_sizing(Gtk::TREE_VIEW_COLUMN_FIXED);
            }
        }

        /* Misc settings to tree view */
        mp_TreeView->set_headers_clickable(true);

        /* Selections */
        m_TreeSelection = mp_TreeView->get_selection();
        m_TreeSelection->set_mode(Gtk::SELECTION_MULTIPLE);

        /* Double click on a row */
        mp_TreeView->signal_row_activated().connect(sigc::mem_fun(*this,&Queue::on_row_activated));

        /* Set up Popupmenu */
        mp_Popup = new QueuePopup(*mp_TreeView);
        mp_Popup->get_action("q_remove").connect(
                sigc::mem_fun(*this,&Queue::on_menu_remove_clicked));
        mp_Popup->get_action("q_add_as_pl").connect(
                sigc::mem_fun(*this,&Queue::on_menu_add_as_pl_clicked));
        mp_Popup->get_action("q_clear").connect(
                sigc::mem_fun(*this,&Queue::on_menu_clear_clicked));
    }

    /*-------------------------------*/
    
    Queue::~Queue(void)
    {
        delete mp_Popup;
    }
    
    /*-------------------------------*/

    void Queue::on_row_activated(const Gtk::TreeModel::Path& path, Gtk::TreeViewColumn* column)
    {
        /* Get the row from the path - Documentation, Y U NO TELL ME?! */
        Gtk::TreeModel::iterator iter = m_refTreeModelFilter->get_iter(path);
        if(iter)
        {
            Gtk::TreeRow row = *iter;
            mp_Client->play_song_at_id(row[m_Columns.m_col_id]);
        }
    }

    /*-------------------------------*/

    void Queue::add_item(void * pSong)
    {
        g_assert(pSong);
        MPD::Song * new_song = (MPD::Song*)pSong;
        Gtk::TreeModel::Row row = *(m_refTreeModel->append());
        row[m_Columns.m_col_id] = new_song->get_id();

        try { /* Check for NULLs just to be sure */
            row[m_Columns.m_col_title] =  new_song->get_tag(MPD_TAG_TITLE,0);
            row[m_Columns.m_col_album] =  new_song->get_tag(MPD_TAG_ALBUM,0);
            row[m_Columns.m_col_artist] = new_song->get_tag(MPD_TAG_ARTIST,0);
        } catch(const std::logic_error& e) {
            Warning("Empty column: %s",e.what());
        }
        delete new_song;
    }

    /*-------------------------------*/

    void Queue::on_entry_activate(void)
    {
        m_FilterText = mp_Entry->get_text();
        m_refTreeModelFilter->refilter();
    }

    /*-------------------------------*/

    void Queue::on_entry_clear_icon(Gtk::EntryIconPosition icon_pos, const GdkEventButton* event)
    {
        if(icon_pos == Gtk::ENTRY_ICON_SECONDARY)
        {
            mp_Entry->set_text("");
            mp_Entry->activate();
        }
    }

    /*-------------------------------*/

    /* Called by search function, looksup if should be filtered out */
    bool Queue::on_filter_row_visible(const Gtk::TreeModel::const_iterator& iter)
    {
        if(iter && !m_FilterText.empty())
        {
            Gtk::TreeRow row = *iter;
            Glib::ustring lower_term = m_FilterText.lowercase();

            Glib::ustring artist = row[m_Columns.m_col_artist];
            if(artist.lowercase().find(lower_term) != Glib::ustring::npos)
                return true;

            Glib::ustring album = row[m_Columns.m_col_album];
            if(album.lowercase().find(lower_term) != Glib::ustring::npos)
                return true;

            Glib::ustring title = row[m_Columns.m_col_title];
            if(title.lowercase().find(lower_term) != Glib::ustring::npos)
                return true;

            return false;
        }
        return true;
    }

    /*-------------------------------*/

    Gtk::Widget * Queue::get_container(void)
    {
        return mp_QueueBox;
    }

    /*-------------------------------*/
            
    void Queue::on_client_update(enum mpd_idle event, MPD::NotifyData& data)
    {
        if(event & (MPD_IDLE_PLAYLIST))
        {
            MPD::Status& status = data.get_status();
            unsigned qv = status.get_queue_version();

            if(qv > m_PlaylistVersion)
            {
                /* TODO: Make use of plchanges 
                 * Refilling always is expensive.
                 * */
                Info("Refilling Queue");
                m_refTreeModel->clear();
                mp_Client->fill_queue(*this);
            }
            
            m_PlaylistVersion = qv;
        }
    }

    /*-------------------------------*/

    void Queue::on_connection_change(bool is_connected)
    {
        /* Empty for now */
    }

    /*-------------------------------*/

    /* Menuhandling */
    void Queue::on_menu_clear_clicked(void)
    {
        mp_Client->queue_clear();
        m_refTreeModel->clear();
    }

    /*-------------------------------*/

    void Queue::on_menu_remove_clicked(void)
    {
        std::vector<Gtk::TreePath> path_row_vec = m_TreeSelection->get_selected_rows();

        if(!path_row_vec.empty())
        {
            mp_Client->begin();

            /* Since we subtract one, we should check this before. */
            for(unsigned it = path_row_vec.size(); it != 0; --it)
            {
                Gtk::TreeModel::iterator rowIt = m_refTreeModel->get_iter(path_row_vec[it-1]);
                if(rowIt)
                {
                    Gtk::TreeRow row = *rowIt;
                    unsigned song_id = row[m_Columns.m_col_id];
                    mp_Client->queue_delete(song_id);
                    m_refTreeModel->erase(rowIt);
                }
            }

            mp_Client->commit();
        }
    }

    /*-------------------------------*/

    void Queue::on_menu_add_as_pl_clicked(void)
    {
        mp_Client->playlist_save("Current");
    }

    /*-------------------------------*/
}
