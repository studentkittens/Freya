#include "Database.hh"
#include "../Log/Writer.hh"
#include "../Utils/Utils.hh"

namespace Browser
{
    DatabaseBrowser::DatabaseBrowser(MPD::Client& client, Glib::RefPtr<Gtk::Builder>& builder) :
        AbstractBrowser("Database")
    {
        mp_Client = &client;
        BUILDER_ADD(builder,"ui/DatabaseBrowser.ui");
        BUILDER_GET(builder,"filebrowser_mainbox",mp_ParentBox);
        BUILDER_GET(builder,"filebrowser_iconview",mp_IView);
        BUILDER_GET(builder,"filebrowser_home",mp_HomeButton);
        BUILDER_GET(builder,"filebrowser_oneup",mp_DirUpButton);
        BUILDER_GET(builder,"filebrowser_statuslabel",mp_StatusLabel);

        m_DirIcon  = Gdk::Pixbuf::create_from_file("gfx/folder.svg");
        m_FileIcon = Gdk::Pixbuf::create_from_file("gfx/songfile.svg");

        m_DirStore = Gtk::ListStore::create(m_Columns);
        mp_IView->set_model(m_DirStore);
        mp_IView->set_markup_column(m_Columns.m_col_name);
        mp_IView->set_pixbuf_column(m_Columns.m_col_icon);

        mp_HomeButton->signal_clicked().connect(sigc::mem_fun(*this,&DatabaseBrowser::on_home_button_clicked));
        mp_IView->signal_item_activated().connect(sigc::mem_fun(*this,&DatabaseBrowser::on_item_activated));

        client.fill_filelist(*this,NULL);
    }

    /*------------------------------------------------*/

    DatabaseBrowser::~DatabaseBrowser(void) {}

    /*------------------------------------------------*/

    Gtk::Widget * DatabaseBrowser::get_container(void)
    {
        return mp_ParentBox;
    }

    /*------------------------------------------------*/
    
    void DatabaseBrowser::add_item(void * pItem)
    {
        g_assert(pItem);
        MPD::Directory * dir = (MPD::Directory*)pItem;
        Gtk::TreeModel::Row row = *(m_DirStore->append());
        row[m_Columns.m_col_name] = Glib::Markup::escape_text(dir->get_path()); 
        row[m_Columns.m_col_icon] = m_DirIcon;
    }

    /*------------------------------------------------*/

    void DatabaseBrowser::on_home_button_clicked(void)
    {
        m_DirStore->clear();
        mp_Client->fill_filelist(*this,NULL);
    }

    /*------------------------------------------------*/

    void DatabaseBrowser::on_item_activated(const Gtk::TreeModel::Path& path)
    {
        Gtk::TreeModel::iterator iter = m_DirStore->get_iter(path);
        if(iter)
        {
            Gtk::TreeRow row = *iter;
            Glib::ustring str = row[m_Columns.m_col_name];
            g_message("Selected: %s\n",str.c_str());
            m_DirStore->clear();
            mp_Client->fill_filelist(*this,str.c_str());
        }
    }

    /*------------------------------------------------*/
}
