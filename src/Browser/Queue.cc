#include "Queue.hh"
#include "../Log/Writer.hh"
#include "../Utils/Utils.hh"

namespace Browser
{
    Queue::Queue(MPD::Client& client, Glib::RefPtr<Gtk::Builder>& builder) :
        AbstractBrowser("Queue",Gtk::Stock::ZOOM_FIT),
        AbstractClientUser(client),
        m_FilterText("")
    {
        
        BUILDER_ADD(builder,"ui/Queue.glade");
        BUILDER_GET(builder,"queue_treeview",mp_TreeView);
        BUILDER_GET(builder,"queue_search_entry",mp_Entry);
        BUILDER_GET(builder,"queue_box",mp_QueueBox);

        mp_Entry->signal_activate().connect(
                sigc::mem_fun(*this,&Queue::on_entry_activate));

        //Create the Tree model:
        m_refTreeModel = Gtk::ListStore::create(m_Columns);
        m_refTreeModelFilter = Gtk::TreeModelFilter::create(m_refTreeModel);
        m_refTreeModelFilter->set_visible_func(
                sigc::mem_fun(*this,&Queue::on_filter_row_visible));

        mp_TreeView->set_model(m_refTreeModelFilter);

        /* Add the TreeView's view columns: */
        //mp_TreeView->append_column("ID", m_Columns.m_col_id);
        //mp_TreeView->append_column("Pos", m_Columns.m_col_pos);
        mp_TreeView->append_column("Artist", m_Columns.m_col_artist);
        mp_TreeView->append_column("Album", m_Columns.m_col_album);
        mp_TreeView->append_column("Title", m_Columns.m_col_title);

        mp_TreeView->set_rules_hint(true);
        mp_TreeView->set_rubber_banding(true);
        mp_TreeView->set_search_column(1);
        mp_TreeView->set_search_entry(*mp_Entry);

        for(guint i = 0; i < 4; i++)
        {
            Gtk::TreeView::Column * pColumn = mp_TreeView->get_column(i);
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
        mp_Popup->get_action("q_remove").connect(sigc::mem_fun(*this,&Queue::on_menu_remove_clicked));
        mp_Popup->get_action("q_playlist_add").connect(sigc::mem_fun(*this,&Queue::on_menu_add_to_pl_clicked));
        mp_Popup->get_action("q_clear").connect(sigc::mem_fun(*this,&Queue::on_menu_clear_clicked));
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
        row[m_Columns.m_col_pos] = new_song->get_pos();

        try { /* Check for NULLs just to be sure */
            row[m_Columns.m_col_title] =  new_song->get_tag(MPD_TAG_TITLE,0);
            row[m_Columns.m_col_album] =  new_song->get_tag(MPD_TAG_ALBUM,0);
            row[m_Columns.m_col_artist] = new_song->get_tag(MPD_TAG_ARTIST,0);
        } catch(const std::logic_error& e) {
            Warning("Empty column: %s",e.what());
        }
    }
    
    /*-------------------------------*/

    void Queue::on_entry_activate(void)
    {
        m_FilterText = mp_Entry->get_text();
        m_refTreeModelFilter->refilter();
    }

    /*-------------------------------*/

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
            /* TODO: Make use of plchanges 
             * Refilling always is expensive.
             * */
            g_printerr("Refill.\n");
            m_refTreeModel->clear();
            mp_Client->fill_queue(*this);
        }
    }
    
    /*-------------------------------*/

    void Queue::on_connection_change(bool is_connected)
    {
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
        // TODO. //
        std::vector<Gtk::TreePath> path_row_vec = m_TreeSelection->get_selected_rows();

        if(!path_row_vec.empty())
        {
            if(path_row_vec.size() == 1)
            {
                Gtk::TreeModel::Path rowPath  = path_row_vec.front();
                Gtk::TreeModel::iterator iter = m_refTreeModel->get_iter(rowPath);
                if(iter)
                {
                    Gtk::TreeRow row = *iter;
                    unsigned song_pos = row[m_Columns.m_col_pos];
                    mp_Client->queue_delete(song_pos);
                    m_refTreeModel->erase(iter);
                }
            }
            else
            {
                /* Song IDs of the last and first song */
                unsigned row_start = UINT_MAX;
                unsigned row_end   = UINT_MAX;

                /* Since we subtract one, we should check this before. */
                for(unsigned it = path_row_vec.size(); it != 0; --it)
                {
                    /* Access! */
                    Gtk::TreeModel::iterator rowIt = m_refTreeModel->get_iter(path_row_vec[it-1]);

                    if(rowIt)
                    {
                        if(it == path_row_vec.size())
                        {
                            Gtk::TreeRow row = *rowIt;
                            row_end = row[m_Columns.m_col_pos];
                        }

                        if(it == 1)
                        {
                            Gtk::TreeRow row = *rowIt;
                            row_start = row[m_Columns.m_col_pos];
                        }

                        m_refTreeModel->erase(rowIt);
                    }
                }

                if(row_start != UINT_MAX && row_end != UINT_MAX)
                {
                    g_message("Deleting: [%d-%d[ + %d",row_start,row_end,row_end);
                    mp_Client->queue_delete_range(row_start,row_end);
                    mp_Client->queue_delete(row_end);
                }
            }
        }
    }

    /*-------------------------------*/

    void Queue::on_menu_add_to_pl_clicked(void)
    {
    }

    /*-------------------------------*/
}
