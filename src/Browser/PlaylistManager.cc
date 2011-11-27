#include "PlaylistManager.hh"
#include "../Utils/Utils.hh"
#include "../Log/Writer.hh"

namespace Browser
{
    PlaylistManager::PlaylistManager(MPD::Client& client, Glib::RefPtr<Gtk::Builder>& builder) :
        AbstractBrowser("Playlists",Gtk::Stock::INDENT)
    {
        mp_Client = &client;

        BUILDER_ADD(builder,"ui/Playlists.glade");
        BUILDER_GET(builder,"playlist_treeview",mp_TreeView);

        /* Get the box and parent it to the main frame */
        Gtk::Box * playlist_box = NULL;
        BUILDER_GET(builder,"playlist_box",playlist_box);
        BUILDER_GET(builder,"playlist_add_pl",mp_AddButton);
        BUILDER_GET(builder,"playlist_delete_pl",mp_DelButton);
        playlist_box->reparent(*this);

        //Create the Tree model:
        m_refTreeModel = Gtk::ListStore::create(m_Columns);
        mp_TreeView->set_model(m_refTreeModel);
        m_Selection = mp_TreeView->get_selection();

        //Add the TreeView's view columns:
        mp_TreeView->append_column("Playlists", m_Columns.m_col_name);
        mp_TreeView->append_column("Songs", m_Columns.m_col_num_songs);
        mp_TreeView->append_column("Last modified", m_Columns.m_col_last_modfied);
        mp_TreeView->set_search_column(0);

        mp_AddButton->signal_clicked().connect(sigc::mem_fun(*this,&PlaylistManager::on_add_clicked));
        mp_DelButton->signal_clicked().connect(sigc::mem_fun(*this,&PlaylistManager::on_del_clicked));
        mp_Client->get_notify().connect(sigc::mem_fun(*this,&PlaylistManager::on_client_change));

        mp_Client->fill_playlists(*this);
        show_all();
    }

    /* ----------------------- */

    Gtk::Widget * PlaylistManager::get_container(void)
    {
        return this;
    }

    /* ----------------------- */

    PlaylistManager::~PlaylistManager(void) {}

    /* ----------------------- */

    void PlaylistManager::add_item(void * pPlaylist)
    {
        g_assert(pPlaylist);
        MPD::Playlist * playlist = (MPD::Playlist*)pPlaylist;
        Gtk::TreeModel::Row row = *(m_refTreeModel->append());
        row[m_Columns.m_col_plist] = playlist;
        row[m_Columns.m_col_name]  = playlist->get_path();
        row[m_Columns.m_col_num_songs] = 42;

        // TODO: Do a util func for this. -> c1
        char timebuf[512] = "Last modified ";
        time_t raw_time = playlist->get_last_modified();
        struct tm * timestamp = localtime(&raw_time);
        strftime(timebuf,512,"%H:%M:%S",timestamp);

        row[m_Columns.m_col_last_modfied] = Glib::ustring("Last modified: ") + timebuf; 
    }
    
    /* ----------------------- */
    
    void PlaylistManager::handle_button_clicks(bool do_add)
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

                std::cerr << pl_name << std::endl;
                mp_Client->playlist_remove(pl_name.c_str());
            }
        }
    }
    
    /* ----------------------- */

    void PlaylistManager::on_add_clicked(void)
    {
       handle_button_clicks(true);
    }
    
    /* ----------------------- */

    void PlaylistManager::on_del_clicked(void)
    {
       handle_button_clicks(false);
    }
    
    /* ----------------------- */

    void PlaylistManager::on_client_change(enum mpd_idle event, MPD::NotifyData& data)
    {
        if(event & MPD_IDLE_STORED_PLAYLIST)
        {
            /* Update the list of playlists */
            m_refTreeModel->clear();
            mp_Client->fill_playlists(*this);
        }
    }
}
