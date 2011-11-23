#include "BrowserList.hh"
#include "../Log/Writer.hh"
#include "../Utils/Utils.hh"

namespace GManager
{
    BrowserList::BrowserList(const Glib::RefPtr<Gtk::Builder>& builder) 
    {
        BUILDER_GET(builder,"plugin_view",mp_PluginListview);

        //Create the Tree model:
        m_refTreeModel = Gtk::ListStore::create(m_Columns);
        mp_PluginListview->set_model(m_refTreeModel);

        /* Get the paned widget */
        BUILDER_GET(builder,"main_paned",mp_Paned);

        /* Get the selection model and connect it to the signal handler */
        m_TreeSelection = mp_PluginListview->get_selection();
        m_TreeSelection->set_mode(Gtk::SELECTION_SINGLE);
        m_TreeSelection->signal_changed().connect(sigc::mem_fun(*this,&BrowserList::on_selection_changed));

        //Fill the TreeView's model
        // TODO ofcourse.
        /*
        Gtk::TreeModel::Row row = *(m_refTreeModel->append());
        row[m_Columns.m_col_name] = "Now Playing";
        row[m_Columns.m_col_name] = "Database";
        row[m_Columns.m_col_name] = "Settings";
        */

        /* Entitle it with "Browsers" */
        mp_PluginListview->append_column("Browsers", m_Columns.m_col_name);
    }

    //----------------------------

    BrowserList::~BrowserList(void) {}

    //----------------------------
   
    void BrowserList::add(AbstractBrowser& browser)
    {
        Gtk::TreeModel::Row row = *(m_refTreeModel->append());
        row[m_Columns.m_col_name] = browser.get_name();
        row[m_Columns.m_col_browser] = &browser;
        //mp_Paned->pack2(*(browser.get_container()),true,true);
    }

    //----------------------------

    void BrowserList::change_browser(AbstractBrowser * browser)
    {
        if(browser != NULL)
        {
            Glib::ustring name = browser->get_name();
            Debug("Adding browser: %s",name.c_str());
            Gtk::Widget * element = mp_Paned->get_child2();
            if(element != NULL)
            {
                mp_Paned->remove(*element);
            }
            mp_Paned->add2(*(browser->get_container()));
        }
        else
        {
            Error("BrowserList has a browser without content.");
        }
    }

    //----------------------------

    void BrowserList::on_selection_changed(void)
    {
        Gtk::TreeModel::iterator iter = m_TreeSelection->get_selected();
        if(iter) 
        {
            Gtk::TreeModel::Row row = *iter;
            change_browser(row[m_Columns.m_col_browser]);
        }
    }
}
