#include "PlaylistManager.hh"
#include "../Utils/Utils.hh"
#include "../Log/Writer.hh"

namespace Browser
{
    PlaylistManager::PlaylistManager(MPD::Client& client, Glib::RefPtr<Gtk::Builder>& builder) :
        AbstractBrowser("Playlists")
    {
        mp_Client = &client;

        try
        {
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
            mp_TreeView->set_search_column(0);

            Gtk::TreeModel::Row row = *(m_refTreeModel->append());
            row[m_Columns.m_col_name] = "Akrea";
            show_all();
        }
        catch(const Gtk::BuilderError& e)
        {
            Error("Could not add playlist ui definitions to builder. Is 'ui/Playlists.glade' okay?");
        }
    }

    /* ----------------------- */

    Gtk::Widget * PlaylistManager::get_container(void)
    {
        return this;
    }

    /* ----------------------- */

    PlaylistManager::~PlaylistManager(void) {}
}
