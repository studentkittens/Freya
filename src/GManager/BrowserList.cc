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

        /* Get the paned widget */
        BUILDER_GET(builder,"main_paned",mp_Paned);


        //Fill the TreeView's model
        // TODO ofcourse.
        Gtk::TreeModel::Row row = *(m_refTreeModel->append());
        row[m_Columns.m_col_name] = "Now Playing";
        row = *(m_refTreeModel->append());
        row[m_Columns.m_col_name] = "Playlists";
        row = *(m_refTreeModel->append());
        row[m_Columns.m_col_name] = "Database";
        row = *(m_refTreeModel->append());
        row[m_Columns.m_col_name] = "Settings";


        /* Entitle it with "Browsers" */
        plugin_listview->append_column("Browsers", m_Columns.m_col_name);
    }

    //----------------------------

    BrowserList::~BrowserList(void) {}

    //----------------------------
    
    void BrowserList::add_name(Glib::ustring& name)
    {
        Gtk::TreeModel::Row row = *(m_refTreeModel->append());
        row[m_Columns.m_col_name] = name;
    }

    //----------------------------
   
    void BrowserList::add(AbstractBrowser& browser)
    {
        add_name(browser.get_name());
        mp_Paned->pack2(*(browser.get_container()),true,true);
    }
}
