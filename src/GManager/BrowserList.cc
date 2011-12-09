#include "BrowserList.hh"
#include "../Log/Writer.hh"
#include "../Utils/Utils.hh"


namespace GManager
{
    BrowserList::BrowserList(MPD::Client& client, const Glib::RefPtr<Gtk::Builder>& builder) :
        AbstractClientUser(client),
        m_NoBrowsers("No Browsers found. This is weird.")
    {
        BUILDER_GET(builder,"plugin_view",mp_PluginListview);

        /* Create the Tree model: */
        m_refTreeModel = Gtk::ListStore::create(m_Columns);
        mp_PluginListview->set_model(m_refTreeModel);

        /* Get the paned widget */
        BUILDER_GET(builder,"main_paned",mp_List);

        /* Get the selection model and connect it to the signal handler */
        m_TreeSelection = mp_PluginListview->get_selection();
        m_TreeSelection->set_mode(Gtk::SELECTION_SINGLE);
        m_TreeSelection->signal_changed().connect(
                sigc::mem_fun(*this,&BrowserList::on_selection_changed));

        /* Entitle it with "Browsers" */
        mp_PluginListview->append_column("", m_Columns.m_col_icon);
        mp_PluginListview->append_column("Browsers", m_Columns.m_col_name);

        mp_List->add(m_NoBrowsers);
        mp_List->show_all();
    }

    //----------------------------

    void BrowserList::on_client_update(enum mpd_idle type, MPD::NotifyData& data)
    {}

    //----------------------------

    void BrowserList::on_connection_change(bool is_connected)
    {
        /* Jump to Settingstab on disconnect,
         * and make other browser insensitive,
         * or make them sensitive on connect again
         * */
        for(Gtk::TreeModel::iterator iter = m_refTreeModel->get_iter("0"); iter; iter++)
        {
            Gtk::TreeRow row = *iter;
            AbstractBrowser * browser = row[m_Columns.m_col_browser];
            if(browser != NULL)
            {
                if(!is_connected && browser->is_visible() && !browser->needs_connection())
                {
                    change_browser(browser);
                }
                else if(browser->needs_connection())
                {
                    Gtk::Widget * container = browser->get_container();
                    if(container != NULL)
                    {
                        container->set_sensitive(is_connected);
                    }
                }
            }
        }
        mp_PluginListview->set_sensitive(is_connected);
    }

    //----------------------------

    void BrowserList::add(AbstractBrowser& browser)
    {
        Gtk::TreeModel::Row row = *(m_refTreeModel->append());
        row[m_Columns.m_col_name] = browser.get_name();
        row[m_Columns.m_col_browser] = &browser;

        /* Render the correct icon */
        row[m_Columns.m_col_icon] = mp_PluginListview->render_icon_pixbuf(
                browser.get_icon_stock_id(),
                Gtk::ICON_SIZE_DND); 
    }

    //----------------------------
    
    void BrowserList::set(AbstractBrowser& browser)
    {
        change_browser(&browser);
    }
    
    //----------------------------

    void BrowserList::change_browser(AbstractBrowser * browser)
    {
        if(browser != NULL)
        {
            Glib::ustring name = browser->get_name();
            Debug("Adding browser: %s",name.c_str());

            /* Get last element of box. Eddy...Duuuude!
             * What did you do earlier here?! */        
            Gtk::Widget* element = mp_List->get_children().back();
            if(element != NULL)
            {
                mp_List->remove(*element);
            }

            mp_List->add(*(browser->get_container()));
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
