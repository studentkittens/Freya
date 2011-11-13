#include "BrowserList.hh"
#include "../Log/Writer.hh"

namespace GManager
{
    BrowserList::BrowserList(const Glib::RefPtr<Gtk::Builder>& builder) 
    {
        try
        {
            Gtk::TreeView * plugin_listview = NULL;
            builder->get_widget("plugin_view",plugin_listview);
            Gtk::manage(plugin_listview);

            //Create the Tree model:
            m_refTreeModel = Gtk::ListStore::create(m_Columns);
            plugin_listview->set_model(m_refTreeModel);

            //Fill the TreeView's model
            Gtk::TreeModel::Row row = *(m_refTreeModel->append());
            row[m_Columns.m_col_name] = "Now Playing";
            row = *(m_refTreeModel->append());
            row[m_Columns.m_col_name] = "Playlist";
            row = *(m_refTreeModel->append());
            row[m_Columns.m_col_name] = "Settings";
            plugin_listview->append_column("Browser", m_Columns.m_col_name);
        }
        catch(const Gtk::BuilderError& e)
        {
            Error("BuilderFailure: %s",e.what().c_str());
        }
    }

    //----------------------------

    BrowserList::~BrowserList(void) {}
}
