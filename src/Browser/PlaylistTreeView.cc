#include "PlaylistTreeView.hh"
#include "../Log/Writer.hh"
#include "../Utils/Utils.hh"

namespace Browser
{
    PlaylistTreeView::PlaylistTreeView(MPD::Client& client) :
        Box(Gtk::ORIENTATION_VERTICAL), AbstractBrowser("Playlist Queue"), m_Entry()
    {
        set_homogeneous(false);
        pack_start(m_ScrolledWindow,true,true);
        pack_start(m_Entry,false,false);

        m_Entry.set_icon_from_stock(Gtk::Stock::CLEAR,Gtk::ENTRY_ICON_SECONDARY);
        m_Entry.set_icon_from_stock(Gtk::Stock::FIND, Gtk::ENTRY_ICON_PRIMARY);

        //Add the TreeView, inside a ScrolledWindow, with the button underneath:
        m_ScrolledWindow.add(m_TreeView);

        //Only show the scrollbars when they are necessary:
        m_ScrolledWindow.set_policy(Gtk::POLICY_AUTOMATIC, Gtk::POLICY_AUTOMATIC);

        //Create the Tree model:
        m_refTreeModel = Gtk::ListStore::create(m_Columns);
        m_TreeView.set_model(m_refTreeModel);

        //Add the TreeView's view columns:
        //This number will be shown with the default numeric formatting.
        m_TreeView.append_column("ID", m_Columns.m_col_id);
        m_TreeView.append_column("Artist", m_Columns.m_col_artist);
        m_TreeView.append_column("Album", m_Columns.m_col_album);
        m_TreeView.append_column("Title", m_Columns.m_col_title);
        m_TreeView.set_rules_hint(true);
        m_TreeView.set_rubber_banding(true);
        m_TreeView.set_search_column(3);
        m_TreeView.set_search_entry(m_Entry);

        for(guint i = 0; i < 4; i++)
        {
            Gtk::TreeView::Column* pColumn = m_TreeView.get_column(i);
            pColumn->set_reorderable();
            pColumn->set_expand(false);
            pColumn->set_resizable(true);
        }

        /* Misc settings to tree view */
        m_TreeView.set_headers_clickable(true);

        /* Selections */
        m_TreeSelection = m_TreeView.get_selection();
        m_TreeSelection->set_mode(Gtk::SELECTION_MULTIPLE);

        /* Double click on a row */
        m_TreeView.signal_row_activated().connect(sigc::mem_fun(*this,&PlaylistTreeView::on_row_activated));

        mp_Client = &client;
        mp_Client->fill_queue(*this);
        show_all();
    }

    /*-------------------------------*/
    
    void PlaylistTreeView::on_row_activated(const Gtk::TreeModel::Path& path, Gtk::TreeViewColumn* column)
    {
        /* Get the row from the path - Documentation, Y U NO TELL ME?! */
        Gtk::TreeModel::iterator iter = m_refTreeModel->get_iter(path);
        if(iter)
        {
            Gtk::TreeRow row = *iter;
            mp_Client->play_song_at_id(row[m_Columns.m_col_id]);
        }
    }

    /*-------------------------------*/

    void PlaylistTreeView::add_item(void * pSong)
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
    }


    /*-------------------------------*/

    PlaylistTreeView::~PlaylistTreeView() {}

    /*-------------------------------*/

    Gtk::Widget * PlaylistTreeView::get_container(void)
    {
        return this;
    }

    /*-------------------------------*/
}
