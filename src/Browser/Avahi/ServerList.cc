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

#include "ServerList.hh"

#include "../../Utils/Utils.hh"
#include "../../Config/Handler.hh"

namespace Browser 
{
    ServerList::ServerList(Glib::RefPtr<Gtk::Builder>& builder,GManager::BrowserList& list) :
        AbstractBrowser(list,"Serverlist",false,false,Gtk::Stock::NETWORK)
    {
        BUILDER_ADD(builder,"ui/AvahiBrowser.glade");
        BUILDER_GET(builder,"avahi_scrolledwindow",avahi_scrl_window);
        BUILDER_GET(builder,"avahi_list",mp_TreeView);
        BUILDER_GET(builder,"avahi_button_select",mp_Button_Select);
        BUILDER_GET(builder,"avahi_button_cancel",mp_Button_Cancel);
        BUILDER_GET(builder,"avahi_status_label",mp_Status_Label);

        /*
         * Backend Signals
         */
        avahi_handle.signal_deleted_server().connect(
                sigc::mem_fun(*this,&ServerList::on_deleted_server));
        avahi_handle.signal_got_server().connect(
                sigc::mem_fun(*this,&ServerList::on_got_server));
        avahi_handle.signal_error_message().connect(
                sigc::mem_fun(*this,&ServerList::on_error_message));

        /* 
         * UI Signals
         */
        mp_Button_Cancel->signal_clicked().connect(
                sigc::mem_fun(*this,&ServerList::on_button_cancel));
        mp_Button_Select->signal_clicked().connect(
                sigc::bind(sigc::mem_fun(*this,&ServerList::on_button_select),builder));

        /*
         * Treeview stuff 
         */
        m_refTreeModel = Gtk::ListStore::create(m_Columns);
        mp_TreeView->set_model(m_refTreeModel);

        mp_TreeView->append_column("IP",         m_Columns.m_col_addr);
        mp_TreeView->append_column("Host",       m_Columns.m_col_hostname);
        mp_TreeView->append_column("Servername", m_Columns.m_col_name);
        mp_TreeView->append_column("Port",       m_Columns.m_col_port);

        avahi_scrl_window->show_all();
    }

    //////////////////////

    Gtk::Widget * ServerList::get_container()
    {
        return avahi_scrl_window;
    }

    //////////////////////

    void ServerList::on_button_cancel()
    {
        get_browser_list().set_previous();
    }

    //////////////////////

    void ServerList::on_button_select(Glib::RefPtr<Gtk::Builder>& builder)
    {
        Glib::RefPtr<Gtk::TreeSelection> refTreeSelection = mp_TreeView->get_selection();
        Gtk::TreeModel::iterator iter = refTreeSelection->get_selected();
        if(iter)
        {
            Gtk::TreeModel::Row row = *iter;

            Glib::ustring new_host = row[m_Columns.m_col_addr];
            unsigned new_port = row[m_Columns.m_col_port];

            CONFIG_SET("settings.connection.host",new_host);
            CONFIG_SET_AS_INT("settings.connection.port",new_port);

            /* 
             * Update the field int the Settings tab..
             * I'm a bit uncertain if this is clean style. 
             *
             * - It works fine anyway.
             */
            Gtk::Entry * ip_textfield;
            Gtk::SpinButton * port_spinbutton;
            BUILDER_GET(builder,"ip_textfield",ip_textfield);
            BUILDER_GET(builder,"port_spinbutton",port_spinbutton);

            port_spinbutton->set_value(new_port);
            ip_textfield->set_text(new_host);


            on_button_cancel();
        }
    }

    //////////////////////

    /* Delete a certain IP */
    void ServerList::on_got_server(Glib::ustring addr, Glib::ustring hostname, Glib::ustring name, unsigned port)
    {
        Gtk::TreeModel::Row row = *(m_refTreeModel->append());

        /* Fill in data */
        row[m_Columns.m_col_addr] = addr;
        row[m_Columns.m_col_hostname] = hostname;
        row[m_Columns.m_col_name] = name;
        row[m_Columns.m_col_port] = port;

        /* Autoselect current row */
        Glib::RefPtr<Gtk::TreeSelection> refTreeSelection = mp_TreeView->get_selection();
        refTreeSelection->select(row);
    }

    ///////////////////////7

    void ServerList::on_deleted_server(Glib::ustring deleted_name)
    {
        if(deleted_name.empty())
            return;

        Gtk::TreeNodeChildren children = m_refTreeModel->children();
        for (Gtk::TreeIter iter = children.begin(); iter != children.end(); ++iter)
        {
            Gtk::TreeRow row = *iter;
            if(row[m_Columns.m_col_name] == deleted_name)
            {
                m_refTreeModel->erase(iter);
                break;
            }
        }
    }

    ///////////////////////7

    void ServerList::on_error_message(Glib::ustring msg)
    {
        mp_Status_Label->set_text(msg);
    }
}
