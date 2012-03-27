/***********************************************************
* This file is part of Freya
* - A free MPD Gtk3 MPD Client -
*
* Authors: Christopher Pahl, Christoph Piechula,
*          Eduard Schneider
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
#include "DatabaseCache.hh"
#include "../../Log/Writer.hh"
#include "../../Utils/Utils.hh"

namespace Browser
{
    Database::Database(MPD::Client& client, Glib::RefPtr<Gtk::Builder>& builder,GManager::BrowserList& list) :
        AbstractBrowser(list,"Database",true,true,Gtk::Stock::DIRECTORY),
        AbstractClientUser(client),
        mp_SearchEntry(NULL)
    {
        /* Instance the Database Cache, a sort of Proxy of MPD::Client */
        mp_Cache = new DatabaseCache(client);

        BUILDER_ADD(builder,"ui/Database.glade");
        BUILDER_GET(builder,"filebrowser_mainbox",mp_ParentBox);
        BUILDER_GET(builder,"filebrowser_iconview",mp_IView);
        BUILDER_GET(builder,"filebrowser_home",mp_HomeButton);
        BUILDER_GET(builder,"filebrowser_oneup",mp_DirUpButton);
        BUILDER_GET(builder,"filebrowser_statuslabel",mp_StatusLabel);
        BUILDER_GET(builder,"filebrowser_search_entry",mp_SearchEntry);

        m_DirIcon  = mp_IView->render_icon_pixbuf(Gtk::Stock::DIRECTORY,Gtk::ICON_SIZE_DIALOG);
        m_FileIcon = mp_IView->render_icon_pixbuf(Gtk::Stock::FILE,Gtk::ICON_SIZE_DIALOG);

        m_DirStore = Gtk::ListStore::create(m_Columns);

        /* Set up Iconview */
        mp_IView->set_model(m_DirStore);
        mp_IView->set_text_column(m_Columns.m_col_name);
        mp_IView->set_pixbuf_column(m_Columns.m_col_icon);

        /* Set up it's signals */
        mp_HomeButton->signal_clicked().connect(
            sigc::mem_fun(*this,&Database::on_home_button_clicked));
        mp_DirUpButton->signal_clicked().connect(
            sigc::mem_fun(*this,&Database::go_one_up));
        mp_IView->signal_item_activated().connect(
            sigc::mem_fun(*this,&Database::on_item_activated));
        mp_SearchEntry->signal_activate().connect(
            sigc::mem_fun(*this,&Database::on_search_entry_activated));


        /* Connect popup menu */
        mp_Popup = new DatabasePopup(*mp_IView);
        mp_Popup->get_action("db_add").connect(
            sigc::mem_fun(*this,&Database::on_menu_db_add_clicked));
        mp_Popup->get_action("db_add_all").connect(
            sigc::mem_fun(*this,&Database::on_menu_db_add_all_clicked));
        mp_Popup->get_action("db_replace").connect(
            sigc::mem_fun(*this,&Database::on_menu_db_replace_clicked));
        mp_Popup->get_action("db_update").connect(
            sigc::mem_fun(*this,&Database::on_menu_db_update_clicked));
        mp_Popup->get_action("db_rescan").connect(
            sigc::mem_fun(*this,&Database::on_menu_db_rescan_clicked));

        /* Key events */
        mp_IView->signal_key_press_event().connect(
            sigc::mem_fun(*this,&Database::on_key_press_handler));

        mp_IView->signal_key_release_event().connect(
            sigc::mem_fun(*this,&Database::on_key_press_handler));

        /* Make icon view react on key events */
        mp_IView->add_events(Gdk::KEY_PRESS_MASK | Gdk::KEY_RELEASE_MASK);
    }

    /*------------------------------------------------*/

    Database::~Database()
    {
        delete mp_Popup;
        delete mp_Cache;
    }

    /* MENU STUFF*/

    void Database::on_menu_db_add_clicked()
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

    void Database::on_menu_db_add_all_clicked()
    {
        /* Add root dir */
        mp_Client->queue_add("/");
    }

    /*------------------------------------------------*/


    void Database::on_menu_db_update_clicked()
    {
        Info("Updating Database.");
        const char * path = mp_Path.c_str();
        path = (path && path[0]) ? path : NULL;
        mp_Client->database_update(path);
    }

    /*------------------------------------------------*/

    void Database::on_menu_db_rescan_clicked()
    {
        Info("Rescanning Database.");
        const char * path = mp_Path.c_str();
        path = (path && path[0]) ? path : NULL;
        mp_Client->database_rescan(path);
    }

    /*------------------------------------------------*/

    void Database::on_menu_db_replace_clicked()
    {
        mp_Client->queue_clear();
        on_menu_db_add_clicked();
    }

    /*------------------------------------------------*/

    Gtk::Widget * Database::get_container()
    {
        return mp_ParentBox;
    }

    /*------------------------------------------------*/

    void Database::add_item(MPD::AbstractComposite * pItem)
    {
        g_assert(pItem);
        bool is_file = pItem->is_leaf();
        const char * path = pItem->get_path();

        if(path != NULL)
        {
            Gtk::TreeModel::Row row = *(m_DirStore->append());
            row[m_Columns.m_col_path] = path;
            row[m_Columns.m_col_name] = Glib::path_get_basename(path);
            row[m_Columns.m_col_icon] = (is_file) ? m_FileIcon : m_DirIcon;
            row[m_Columns.m_col_is_file] = is_file;
        }
    }

    /*------------------------------------------------*/

    void Database::on_home_button_clicked()
    {
        set_current_path("/");
    }

    /*------------------------------------------------*/

    void Database::on_item_activated(const Gtk::TreeModel::Path& path)
    {
        Gtk::TreeModel::iterator iter = m_DirStore->get_iter(path);
        if(iter)
        {
            Gtk::TreeRow row = *iter;
            Glib::ustring path = row[m_Columns.m_col_path];
            if(row[m_Columns.m_col_is_file] == false)
            {
                set_current_path(path.c_str());
            }
            else
            {
                on_menu_db_add_clicked();
            }
        }
    }

    /*------------------------------------------------*/
    /* ---------------- LOGIC ----------------------- */
    /*------------------------------------------------*/

    void Database::set_current_path(const char * path)
    {
        mp_Path = path;
        m_DirStore->clear();
        mp_Cache->fill_filelist(*this,path);
        mp_StatusLabel->set_text((mp_Path != "/") ? ("/" + mp_Path) : "/");
    }

    /*------------------------------------------------*/

    void Database::go_one_up()
    {
        std::string dir_up = Glib::path_get_dirname(mp_Path);

        if(dir_up == ".")
            dir_up = "/";

        set_current_path(dir_up.c_str());
    }

    /*------------------------------------------------*/
    /* --------------- Client Updates --------------- */
    /*------------------------------------------------*/

    void Database::on_client_update(enum mpd_idle event, MPD::NotifyData& data)
    {
        if(event & MPD_IDLE_DATABASE)
        {
            set_current_path(mp_Path.c_str());
        }
    }

    /*------------------------------------------------*/

    void Database::on_connection_change(bool server_changed, bool is_connected)
    {
        /* Go back to root when server changed */
        if(server_changed)
        {
            set_current_path("/");
        }
    }

    /*------------------------------------------------*/
    /*------------------------------------------------*/

    void Database::focus_item_starting_with(const char * prefix)
    {
        if(prefix == NULL)
            return;

        unsigned cursor  = 0;

        Glib::ustring strPrefix(prefix);
        strPrefix = strPrefix.lowercase();

        for(Gtk::TreeModel::iterator iter = m_DirStore->get_iter("0"); iter; iter++)
        {
            Gtk::TreeRow row = *iter;
            Glib::ustring row_str = row[m_Columns.m_col_name];

            if(row_str.lowercase().compare(strPrefix) == 0)
            {
                Gtk::TreePath focus_path(Utils::int_to_string(cursor));
                mp_IView->select_path(focus_path);
                break;
            }
            cursor++;
        }
    }

    /*------------------------------------------------*/

    void Database::on_search_entry_activated() 
    {
        Glib::ustring search_term = mp_SearchEntry->get_text();
        if(search_term.empty())
        {
            set_current_path("/");
        }
        else
        {
            m_DirStore->clear();

            MPD::Query * search = mp_Client->create_db_songs_query(false);
            if(search != NULL)
            {
                MPD::SongVector songvec;
                search->add_tag_constraint(MPD_TAG_ARTIST,search_term.c_str());
                search->commit(songvec);

                for(MPD::SongVector::iterator it = songvec.begin(); it != songvec.end(); it++)
                {
                    MPD::Song * song = *it;
                    if(song != NULL)
                    {
                        add_item(song);
                        delete song;
                    }
                }

                delete search;
            }
        }
    }

    /*------------------------------------------------*/

    bool Database::on_key_press_handler(GdkEventKey * event)
    {
        g_assert(event);
        if(event->type   == GDK_KEY_RELEASE &&
                event->keyval == GDK_KEY_BackSpace)
        {
            go_one_up();
            return true;
        }
        else if(event->type == GDK_KEY_RELEASE &&
                event->keyval >= GDK_KEY_0 &&
                event->keyval <= GDK_KEY_z)
        {
            gchar * key_name = gdk_keyval_name(event->keyval);
            focus_item_starting_with(key_name);
        }

        return false;
    }
}
