 /***********************************************************
* This file is part of Freya 
* - A free MPD Gtk3 MPD Client -
* 
* Authors: Christopher Pahl, Christoph Piechula,
*          Eduard Schneider, Marc Tigges
*
* Copyright (C) [2011-2012]
* Hosted at: https://github.com/studentkittens/Freya
*
*              __..--''``---....___   _..._    __
*    /// //_.-'    .-/";  `        ``<._  ``.''_ `. / // /
*   ///_.-' _..--.'_                        `( ) ) // //
*   / (_..-' // (< _     ;_..__               ; `' / ///
*    / // // //  `-._,_)' // / ``--...____..-' /// / //  
*  Ascii-Art by Felix Lee <flee@cse.psu.edu>
*
* Freya is free software: you can redistribute it and/or modify
* it under the terms of the GNU General Public License as published by
* the Free Software Foundation, either version 3 of the License, or
* (at your option) any later version.
*
* Freya is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
* GNU General Public License for more details.
*
* You should have received a copy of the GNU General Public License
* along with Freya. If not, see <http://www.gnu.org/licenses/>.
**************************************************************/
#include "Database.hh"
#include "../Log/Writer.hh"
#include "../Utils/Utils.hh"

using namespace std;

namespace Browser
{
    DatabaseBrowser::DatabaseBrowser(MPD::Client& client, Glib::RefPtr<Gtk::Builder>& builder) :
        AbstractBrowser("Database",true,true,Gtk::Stock::DIRECTORY),
        AbstractClientUser(client)
    {
        BUILDER_ADD(builder,"ui/Database.glade");
        BUILDER_GET(builder,"filebrowser_mainbox",mp_ParentBox);
        BUILDER_GET(builder,"filebrowser_iconview",mp_IView);
        BUILDER_GET(builder,"filebrowser_home",mp_HomeButton);
        BUILDER_GET(builder,"filebrowser_oneup",mp_DirUpButton);
        BUILDER_GET(builder,"filebrowser_statuslabel",mp_StatusLabel);

        m_DirIcon  = mp_IView->render_icon_pixbuf(Gtk::Stock::DIRECTORY,Gtk::ICON_SIZE_DIALOG);
        m_FileIcon = mp_IView->render_icon_pixbuf(Gtk::Stock::FILE,Gtk::ICON_SIZE_DIALOG);

        m_DirStore = Gtk::ListStore::create(m_Columns);

        /* Set up Iconview */
        mp_IView->set_model(m_DirStore);
        mp_IView->set_text_column(m_Columns.m_col_name);
        mp_IView->set_pixbuf_column(m_Columns.m_col_icon);

        /* Set up it's signals */
        mp_HomeButton->signal_clicked().connect(
                sigc::mem_fun(*this,&DatabaseBrowser::on_home_button_clicked));
        mp_DirUpButton->signal_clicked().connect(
                sigc::mem_fun(*this,&DatabaseBrowser::go_one_up));
        mp_IView->signal_item_activated().connect(
                sigc::mem_fun(*this,&DatabaseBrowser::on_item_activated));

        /* Connect popup menu */
        mp_Popup = new DatabasePopup(*mp_IView); 
        mp_Popup->get_action("db_add").connect(
                sigc::mem_fun(*this,&DatabaseBrowser::on_menu_db_add_clicked));
        mp_Popup->get_action("db_add_all").connect(
                sigc::mem_fun(*this,&DatabaseBrowser::on_menu_db_add_all_clicked));
        mp_Popup->get_action("db_replace").connect(
                sigc::mem_fun(*this,&DatabaseBrowser::on_menu_db_replace_clicked));
        mp_Popup->get_action("db_update").connect(
                sigc::mem_fun(*this,&DatabaseBrowser::on_menu_db_update_clicked));
        mp_Popup->get_action("db_rescan").connect(
                sigc::mem_fun(*this,&DatabaseBrowser::on_menu_db_rescan_clicked));

        /* An empy path means root */
        set_current_path("");
    }
    
    /*------------------------------------------------*/

    DatabaseBrowser::~DatabaseBrowser(void) 
    {
        delete mp_Popup;
    }

    /* MENU STUFF*/

    void DatabaseBrowser::on_menu_db_add_clicked(void)
    {
        std::vector<Gtk::TreePath> items = mp_IView->get_selected_items();

        /* This makes the loop a active section */
        mp_Client->begin();
        for(unsigned i = items.size(); i != 0; --i)
        {
            Gtk::TreeModel::iterator iter = m_DirStore->get_iter(items[i-1]);
            if(iter)
            {
                Gtk::TreeRow row = *iter;
                Glib::ustring path = row[m_Columns.m_col_path];
                mp_Client->queue_add(path.c_str());
            }
        }

        /* Commit queued add commands */
        mp_Client->commit();
    }

    /*------------------------------------------------*/
    
    void DatabaseBrowser::on_menu_db_add_all_clicked(void)
    {
        /* Add root dir */
        mp_Client->queue_add("/");
    }

    /*------------------------------------------------*/
    
    
    void DatabaseBrowser::on_menu_db_update_clicked(void)
    {
        Info("Updating Database.");
        const char * path = mp_Path.c_str();
        path = (path && path[0]) ? path : NULL;
        mp_Client->database_update(path);
    }
    
    /*------------------------------------------------*/
    
    void DatabaseBrowser::on_menu_db_rescan_clicked(void)
    {
        Info("Updating Database.");
        const char * path = mp_Path.c_str();
        path = (path && path[0]) ? path : NULL;
        mp_Client->database_rescan(path);
    }
    
    /*------------------------------------------------*/
    
    void DatabaseBrowser::on_menu_db_replace_clicked(void)
    {
        mp_Client->queue_clear();
        on_menu_db_add_clicked();
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
        delete pDir;
    }

    /*------------------------------------------------*/

    void DatabaseBrowser::add_song_file(MPD::Song * pSong)
    {
        g_assert(pSong);
        add_item(pSong->get_uri(),true);
        delete pSong;
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
    
    void DatabaseBrowser::on_client_update(enum mpd_idle event, MPD::NotifyData& data)
    {
        if(event & MPD_IDLE_DATABASE)
        {
            set_current_path(mp_Path.c_str());
        }
    }
    
    /*------------------------------------------------*/
    
    void DatabaseBrowser::on_connection_change(bool is_connected)
    {
        /* Empty for now */
    }
    
    /*------------------------------------------------*/
}
