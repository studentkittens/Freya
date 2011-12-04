#include "PlaylistManager.hh"
#include "../Utils/Utils.hh"
#include "../Log/Writer.hh"

namespace Browser
{
    PlaylistManager::PlaylistManager(MPD::Client& client, Glib::RefPtr<Gtk::Builder>& builder) :
        AbstractBrowser("Playlists",Gtk::Stock::INDENT),
        AbstractClientUser(client)
    {
        BUILDER_ADD(builder,"ui/Playlists.glade");
        BUILDER_GET(builder,"playlist_treeview",mp_TreeView);

        /* Get the box and parent it to the main frame */
        Gtk::Box * playlist_box = NULL;
        BUILDER_GET(builder,"playlist_box",playlist_box);
        BUILDER_GET(builder,"playlist_add_pl",mp_AddButton);
        BUILDER_GET(builder,"playlist_delete_pl",mp_DelButton);
        playlist_box->reparent(*this);

        /* Render playlist icon */
        m_PlaylistIcon = mp_TreeView->render_icon_pixbuf(Gtk::Stock::INDENT,Gtk::ICON_SIZE_BUTTON);

        /* Create the Tree model */
        m_refTreeModel = Gtk::ListStore::create(m_Columns);
        mp_TreeView->set_model(m_refTreeModel);
        m_Selection = mp_TreeView->get_selection();

        /* Add the TreeView's view columns */
        mp_TreeView->append_column("", m_Columns.m_col_icon);
        mp_TreeView->append_column_editable("Playlists", m_Columns.m_col_name);
        mp_TreeView->append_column("Last modiefied", m_Columns.m_col_last_modfied);
        mp_TreeView->set_search_column(0);

        /* Connect buttons in bar */
        mp_AddButton->signal_clicked().connect(sigc::mem_fun(*this,&PlaylistManager::on_add_clicked));
        mp_DelButton->signal_clicked().connect(sigc::mem_fun(*this,&PlaylistManager::on_menu_del_clicked));

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
                Glib::ustring pl_name = row[m_Columns.m_col_name];

                if(load_or_remove)
                {
                    mp_Client->playlist_load(pl_name.c_str());
                }
                else
                {
                    mp_Client->playlist_remove(pl_name.c_str());
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
            m_refTreeModel->clear();
            mp_Client->fill_playlists(*this);
        }
    }
    
    /* ----------------------- */

    void PlaylistManager::on_connection_change(bool is_connected)
    {
        /* Empty for now */
    }
}
