#include "PlaylistTreeView.hh"
#include "../Log/Writer.hh"
#include "../Utils/Utils.hh"

namespace GManager
{
    PlaylistTreeView::PlaylistTreeView(const Glib::RefPtr<Gtk::Builder>& builder)
    {
        add(m_ScrolledWindow);

        //Add the TreeView, inside a ScrolledWindow, with the button underneath:
        m_ScrolledWindow.add(m_TreeView);

        //Only show the scrollbars when they are necessary:
        m_ScrolledWindow.set_policy(Gtk::POLICY_AUTOMATIC, Gtk::POLICY_AUTOMATIC);

        //Create the Tree model:
        m_refTreeModel = Gtk::ListStore::create(m_Columns);
        m_TreeView.set_model(m_refTreeModel);

        for(int i = 0; i < 420; i++)
        {
            //Fill the TreeView's model
            Gtk::TreeModel::Row row = *(m_refTreeModel->append());
            row[m_Columns.m_col_id] = i;
            row[m_Columns.m_col_title] = "Trugbild                ";
            row[m_Columns.m_col_album] = "Ein Leben Lang          ";
            row[m_Columns.m_col_artist] = "Akrea                  ";
        }

        //Add the TreeView's view columns:
        //This number will be shown with the default numeric formatting.
        m_TreeView.append_column("ID", m_Columns.m_col_id);
        m_TreeView.append_column("Title", m_Columns.m_col_title);
        m_TreeView.append_column("Album", m_Columns.m_col_album);
        m_TreeView.append_column("Artist", m_Columns.m_col_artist);

        for(guint i = 0; i < 3; i++)
        {
            Gtk::TreeView::Column* pColumn = m_TreeView.get_column(i);
            pColumn->set_reorderable();
        }

        Gtk::Box * main_box;
        BUILDER_GET(builder,"main_box",main_box);
        main_box->pack_start(*this,true,true);

        /* Misc settings to tree view */
        m_TreeView.set_headers_clickable(true);

        show_all();
    }

    PlaylistTreeView::~PlaylistTreeView() {}
}
