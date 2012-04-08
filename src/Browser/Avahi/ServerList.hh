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
#ifndef FREYA_AVAHI_SERVERLIST_HH
#define FREYA_AVAHI_SERVERLIST_HH

#include "../../../config.h"

#include <gtkmm.h>
#include "../../Avahi/Browser.hh"
#include "../AbstractBrowser.hh"

namespace Browser
{
class ServerList : public AbstractBrowser
{
public:
    ServerList(Glib::RefPtr<Gtk::Builder>& builder,GManager::BrowserList& list);

    Gtk::Widget * get_container();

protected:

    /* Signal handlers */
    void on_button_cancel();
    void on_button_select(Glib::RefPtr<Gtk::Builder>& builder);

    void on_got_server(Glib::ustring addr, Glib::ustring hostname, Glib::ustring name, unsigned port);
    void on_deleted_server(Glib::ustring deleted_name);
    void on_error_message(Glib::ustring msg);

    /* Treemodel def */
    class ModelColumns : public Gtk::TreeModel::ColumnRecord
    {
    public:

        ModelColumns()
        {
            add(m_col_addr);
            add(m_col_hostname);
            add(m_col_name);
            add(m_col_port);
        }

        Gtk::TreeModelColumn<Glib::ustring> m_col_addr;
        Gtk::TreeModelColumn<Glib::ustring> m_col_hostname;
        Gtk::TreeModelColumn<Glib::ustring> m_col_name;
        Gtk::TreeModelColumn<unsigned int>  m_col_port;
    };

    ///////////////////////

    Gtk::ScrolledWindow * avahi_scrl_window;
    Gtk::TreeView * mp_TreeView;
    Gtk::Button * mp_Button_Cancel, * mp_Button_Select;
    Gtk::Label * mp_Status_Label;

    Glib::RefPtr<Gtk::ListStore> m_refTreeModel;
    ModelColumns m_Columns;

    Avahi::Browser avahi_handle;
};

}

#endif // FREYA_AVAHI_SERVERLIST_HH
