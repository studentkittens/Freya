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
        playlist_box->reparent(*this);

        //Create the Tree model:
        m_refTreeModel = Gtk::ListStore::create(m_Columns);
        mp_TreeView->set_model(m_refTreeModel);

        //Add the TreeView's view columns:
        mp_TreeView->append_column("Playlists", m_Columns.m_col_name);
        mp_TreeView->append_column("Songs", m_Columns.m_col_num_songs);
        mp_TreeView->append_column("Last modiefied", m_Columns.m_col_last_modfied);
        mp_TreeView->set_search_column(0);

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

        // TODO: Do a util func for this.
        char timebuf[512] = "Last modified ";
        time_t raw_time = playlist->get_last_modified();
        struct tm * timestamp = localtime(&raw_time);
        strftime(timebuf,512,"%H:%M:%S",timestamp);

        row[m_Columns.m_col_last_modfied] = Glib::ustring("Last modified: ") + timebuf; 
    }
}
