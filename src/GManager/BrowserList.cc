#include "BrowserList.hh"
#include "../Log/Writer.hh"
#include "../Utils/Utils.hh"

#define FORTUNE_BUF_SIZE 1024

namespace GManager
{
    BrowserList::BrowserList(MPD::Client& client, const Glib::RefPtr<Gtk::Builder>& builder) :
        AbstractGElement(client)
    {
        BUILDER_GET(builder,"plugin_view",mp_PluginListview);

        /* Create the Tree model: */
        m_refTreeModel = Gtk::ListStore::create(m_Columns);
        mp_PluginListview->set_model(m_refTreeModel);

        /* Get the paned widget */
        BUILDER_GET(builder,"main_paned",mp_Paned);

        /* Get the selection model and connect it to the signal handler */
        m_TreeSelection = mp_PluginListview->get_selection();
        m_TreeSelection->set_mode(Gtk::SELECTION_SINGLE);
        m_TreeSelection->signal_changed().connect(
                sigc::mem_fun(*this,&BrowserList::on_selection_changed));

        /* Entitle it with "Browsers" */
        mp_PluginListview->append_column("", m_Columns.m_col_icon);
        mp_PluginListview->append_column("Browsers", m_Columns.m_col_name);

        /* Setup startscreen (fortunes) */
        Gtk::ScrolledWindow * fortune_scrl_window = NULL;
        Gtk::Button * fortune_refresh = NULL;
        BUILDER_ADD(builder,"ui/Startscreen.glade");
        BUILDER_GET(builder,"fortune_scrolledwindow",fortune_scrl_window);
        BUILDER_GET(builder,"fortune_label",mp_FortuneLabel);
        BUILDER_GET(builder,"fortune_refresh",fortune_refresh);

        fortune_refresh->signal_clicked().connect(sigc::mem_fun(*this,&BrowserList::on_refresh_fortune));
        on_refresh_fortune();        

        mp_Paned->add(*fortune_scrl_window);
        mp_Paned->show_all();
    }

    //----------------------------

    void BrowserList::on_client_update(enum mpd_idle type, MPD::NotifyData& data)
    {
        //TODO
    }

    //----------------------------

    void BrowserList::on_connection_change(bool is_connected)
    {
        //TODO
    }

    //----------------------------
    
    void BrowserList::on_refresh_fortune(void)
    {
        Glib::ustring fortune = get_fortune();
        if(!fortune.empty())
        {
            mp_FortuneLabel->set_markup(fortune);
        }
    }
    
    //----------------------------

    Glib::ustring BrowserList::get_fortune(void)
    {
        FILE * pipe = NULL;
        const char * const command = "fortune -s -n 340";
        Glib::ustring retv = "";

        if((pipe = popen(command,"r")))
        {
            char fortune_buf[FORTUNE_BUF_SIZE];
            int bytes = fread(fortune_buf,1,FORTUNE_BUF_SIZE,pipe);
            if(bytes != 0 && !strstr(fortune_buf,"fortune:"))
            {
                char * last_newline = strrchr(fortune_buf,'\n');
                if(last_newline != NULL)
                    last_newline[0] = 0;

                retv = Glib::Markup::escape_text(fortune_buf);
                retv.insert(0,"<span font='15.0' weight='light'>");
                retv.append("</span>");

            }
            pclose(pipe);
        }
        return retv;
    }

    //----------------------------

    void BrowserList::add(AbstractBrowser& browser)
    {
        Gtk::TreeModel::Row row = *(m_refTreeModel->append());
        row[m_Columns.m_col_name] = browser.get_name();
        row[m_Columns.m_col_browser] = &browser;
        row[m_Columns.m_col_icon] = mp_PluginListview->render_icon_pixbuf(
                browser.get_icon_stock_id(),
                Gtk::ICON_SIZE_DND); 
    }

    //----------------------------

    void BrowserList::change_browser(AbstractBrowser * browser)
    {
        if(browser != NULL)
        {
            Glib::ustring name = browser->get_name();
            Debug("Adding browser: %s",name.c_str());
            Gtk::Widget * element;

            Glib::ListHandle<Gtk::Widget*>  children = mp_Paned->get_children();
            for(Glib::ListHandle<Gtk::Widget*>::iterator it=children.begin(); it != children.end(); it++)
            {
                element = *it;
            }

            if(element != NULL)
            {
                mp_Paned->remove(*element);
            }
            mp_Paned->add(*(browser->get_container()));
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
