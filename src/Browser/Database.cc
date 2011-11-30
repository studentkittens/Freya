#include "Database.hh"
#include "../Log/Writer.hh"
#include "../Utils/Utils.hh"

namespace Browser
{
    DatabaseBrowser::DatabaseBrowser(MPD::Client& client, Glib::RefPtr<Gtk::Builder>& builder) :
        AbstractBrowser("Database",Gtk::Stock::DIRECTORY)
    {
        mp_Client = &client;
        BUILDER_ADD(builder,"ui/Database.glade");
        BUILDER_GET(builder,"filebrowser_mainbox",mp_ParentBox);
        BUILDER_GET(builder,"filebrowser_iconview",mp_IView);
        BUILDER_GET(builder,"filebrowser_home",mp_HomeButton);
        BUILDER_GET(builder,"filebrowser_oneup",mp_DirUpButton);
        BUILDER_GET(builder,"filebrowser_statuslabel",mp_StatusLabel);

        m_DirIcon  = mp_IView->render_icon_pixbuf(Gtk::Stock::DIRECTORY,Gtk::ICON_SIZE_DIALOG);
        m_FileIcon = mp_IView->render_icon_pixbuf(Gtk::Stock::FILE,Gtk::ICON_SIZE_DIALOG);

        m_DirStore = Gtk::ListStore::create(m_Columns);
        mp_IView->set_model(m_DirStore);
        mp_IView->set_text_column(m_Columns.m_col_name);
        mp_IView->set_pixbuf_column(m_Columns.m_col_icon);

        mp_HomeButton->signal_clicked().connect(
                sigc::mem_fun(*this,&DatabaseBrowser::on_home_button_clicked));
        mp_DirUpButton->signal_clicked().connect(
                sigc::mem_fun(*this,&DatabaseBrowser::go_one_up));
        mp_IView->signal_item_activated().connect(
                sigc::mem_fun(*this,&DatabaseBrowser::on_item_activated));

        /* Connect popup menu */
        mp_Popup = new DatabasePopup(*mp_IView); 
        
        set_current_path("");
    }

    /*------------------------------------------------*/

    DatabaseBrowser::~DatabaseBrowser(void) 
    {
        delete mp_Popup;
    }

    /*------------------------------------------------*/

    Gtk::Widget * DatabaseBrowser::get_container(void)
    {
        return mp_ParentBox;
    }

    /*------------------------------------------------*/
    
    void DatabaseBrowser::add_directory(MPD::Directory * pDir)
    {
        g_assert(pDir);
        add_item(pDir->get_path(),false);
    }
    
    /*------------------------------------------------*/

    void DatabaseBrowser::add_song_file(MPD::Song * pSong)
    {
        g_assert(pSong);
        add_item(pSong->get_uri(),true);
    }
    
    /*------------------------------------------------*/

    void DatabaseBrowser::add_item(const char * path, bool is_file)
    {
        g_assert(path);
        Gtk::TreeModel::Row row = *(m_DirStore->append());
        row[m_Columns.m_col_path] = path;
        row[m_Columns.m_col_name] = Glib::path_get_basename(path);
        row[m_Columns.m_col_icon] = (is_file) ? m_FileIcon : m_DirIcon;
        row[m_Columns.m_col_is_file] = is_file;
    }

    /*------------------------------------------------*/

    void DatabaseBrowser::on_home_button_clicked(void)
    {
        m_DirStore->clear();
        mp_Client->fill_filelist(*this,NULL);
        set_current_path("");
    }

    /*------------------------------------------------*/

    void DatabaseBrowser::on_item_activated(const Gtk::TreeModel::Path& path)
    {
        Gtk::TreeModel::iterator iter = m_DirStore->get_iter(path);
        if(iter)
        {
            Gtk::TreeRow row = *iter;
            if(row[m_Columns.m_col_is_file] == false)
            {
                Glib::ustring path = row[m_Columns.m_col_path];
                set_current_path(path.c_str());
            }
        }
    }

    /*------------------------------------------------*/

    void DatabaseBrowser::set_current_path(const char * path)
    {
        mp_Path = path;
        m_DirStore->clear();
        mp_Client->fill_filelist(*this,mp_Path.c_str());
        mp_StatusLabel->set_text(!mp_Path.empty() ? mp_Path : "Root");
    }

    /*------------------------------------------------*/

    void DatabaseBrowser::go_one_up(void)
    {
        std::string dir_up = Glib::path_get_dirname(mp_Path);

        if(dir_up == ".")
            dir_up = "";

        set_current_path(dir_up.c_str());
    }

    /*------------------------------------------------*/
}
