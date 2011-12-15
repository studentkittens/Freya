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
#include <gdk/gdkkeysyms.h> 

using namespace std;

namespace Browser
{
    Queue::Queue(MPD::Client& client, Glib::RefPtr<Gtk::Builder>& builder) :
        AbstractBrowser("Queue",true,true,Gtk::Stock::ZOOM_FIT),
        AbstractClientUser(client),
        m_FilterText(""),
        mp_CurrentSong(NULL)
    {
        BUILDER_ADD(builder,"ui/Queue.glade");
        BUILDER_GET(builder,"queue_treeview",mp_TreeView);
        BUILDER_GET(builder,"queue_search_entry",mp_Entry);
        BUILDER_GET(builder,"queue_box",mp_QueueBox);

        /* Create the Tree model */
        m_refTreeModel = Gtk::ListStore::create(m_Columns);
        m_refTreeModelFilter = Gtk::TreeModelFilter::create(m_refTreeModel);
        mp_TreeView->set_model(m_refTreeModelFilter);
        
        /* Create the merger, it handles the updating of the queue */
        mp_Merger = new QueueMerger(client,m_refTreeModel,m_Columns); 

        configure_signals();
        configure_columns();

        /* Selections */
        m_TreeSelection = mp_TreeView->get_selection();
        m_TreeSelection->set_mode(Gtk::SELECTION_MULTIPLE);

        /* Init the playlist add dialog */
        mp_AddDialog = new PlaylistAddDialog(client,builder);

        /* Make TreeView react on Keyevents */
        mp_TreeView->add_events(Gdk::KEY_PRESS_MASK | Gdk::KEY_RELEASE_MASK);
    }

    /*-------------------------------*/
    
    Queue::~Queue(void)
    {
        delete mp_Popup;
        delete mp_AddDialog;
        delete mp_CurrentSong;
        delete mp_Merger;
    }
    
    /*-------------------------------*/
    
    void Queue::configure_signals(void)
    {
        /* Start searching */
        mp_Entry->signal_activate().connect(
                sigc::mem_fun(*this,&Queue::on_entry_activate));

        m_refTreeModelFilter->set_visible_func(
                sigc::mem_fun(*this,&Queue::on_filter_row_visible));

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

        /* Key events */
        mp_TreeView->signal_key_press_event().connect(
                sigc::mem_fun(*this,&Queue::on_key_press_handler));

        mp_TreeView->signal_key_release_event().connect(
                sigc::mem_fun(*this,&Queue::on_key_press_handler));
    }
    
    /*-------------------------------*/
    
    void Queue::configure_columns(void)
    {
        /* Add the TreeView's view columns: */
        /* Useful for debugging purpose */
        //mp_TreeView->append_column("Pos", m_Columns.m_col_pos);
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

    void Queue::on_entry_activate(void)
    {
        m_FilterText = mp_Entry->get_text();
        m_refTreeModelFilter->refilter();
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
        if(event & (MPD_IDLE_PLAYER))
        {
            /* Delete old song, retrieve new and copy it */
            delete mp_CurrentSong;
            MPD::Song * to_copy = data.get_song();

            if(to_copy != NULL)
            {
                mp_CurrentSong = new MPD::Song(*to_copy);
            }
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
        //TODO: Might get more efficient here.
        std::vector<Gtk::TreePath> path_row_vec = m_TreeSelection->get_selected_rows();

        if(!path_row_vec.empty())
        {
            unsigned first_pos = 0;

            mp_Merger->disable_merge_once();
            mp_Client->begin();

            /* Since we subtract one, we should check this before. */
            for(unsigned it = path_row_vec.size(); it != 0; --it)
            {
                Gtk::TreeModel::iterator rowIt = m_refTreeModel->get_iter(path_row_vec[it-1]);
                if(rowIt)
                {
                    Gtk::TreeRow row = *rowIt;
                    first_pos = row[m_Columns.m_col_pos];

                    unsigned song_id = row[m_Columns.m_col_id];
                    mp_Client->queue_delete(song_id);
                    m_refTreeModel->erase(rowIt);
                }
            }

            /* Commit and update queue for the sake of efficiency.. */
            mp_Client->commit();
            mp_Merger->recalculate_positions(first_pos);
        }
    }

    /*-------------------------------*/

    void Queue::on_menu_add_as_pl_clicked(void)
    {
        mp_AddDialog->run();
    }

    /*-------------------------------*/

    bool Queue::on_key_press_handler(GdkEventKey * event)
    {
        g_assert(event);
        if(event->type   == GDK_KEY_RELEASE &&
           event->keyval == GDK_KEY_space   &&
           mp_CurrentSong != NULL)
        {
            char buf[42] = {0};
            g_snprintf(buf,100,"%d",mp_CurrentSong->get_pos());

            mp_TreeView->set_cursor(Gtk::TreePath(buf));
            return true;
        }
        else if(event->type   == GDK_KEY_RELEASE  &&
                event->state  &  (GDK_CONTROL_MASK|GDK_SHIFT_MASK) &&
                event->keyval == GDK_KEY_f)
        {
            mp_Entry->grab_focus();
            return true;
        }
        return false;
    }

    /*-------------------------------*/
}
