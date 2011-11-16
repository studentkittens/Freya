#include "BrowserList.hh"
#include "../Log/Writer.hh"
#include "../Utils/Utils.hh"

namespace GManager
{
    BrowserList::BrowserList(const Glib::RefPtr<Gtk::Builder>& builder) 
    {
        BUILDER_GET(builder,"plugin_view",plugin_listview);

        //Create the Tree model:
        m_refTreeModel = Gtk::ListStore::create(m_Columns);
        plugin_listview->set_model(m_refTreeModel);

        //Fill the TreeView's model
        Gtk::TreeModel::Row row = *(m_refTreeModel->append());
        row[m_Columns.m_col_name] = "Now Playing";
        row = *(m_refTreeModel->append());
        row[m_Columns.m_col_name] = "Queue";
        row = *(m_refTreeModel->append());
        row[m_Columns.m_col_name] = "Settings";
        plugin_listview->append_column("Browser", m_Columns.m_col_name);
    }

    //----------------------------

    BrowserList::~BrowserList(void) {}
}
