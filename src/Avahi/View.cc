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
#include "View.hh"

namespace Avahi
{
    View::View(void) :
        Gtk::Window(Gtk::WINDOW_TOPLEVEL),
        m_VBox(Gtk::ORIENTATION_HORIZONTAL,2),
        m_Button_Cancel("Cancel"),
        m_Button_Select("Select"),
        m_Status_Label("Searching..")
    {
        set_title("MPD Serverlist");
        set_border_width(5);
        set_default_size(400, 200);

        /* Modality */
        set_modal(true);

        add(m_VBox);

        /* Add the TreeView, inside a ScrolledWindow, with the button underneath: */
        m_ScrolledWindow.add(m_TreeView);

        /* Only show the scrollbars when they are necessary: */
        m_ScrolledWindow.set_policy(Gtk::POLICY_AUTOMATIC, Gtk::POLICY_AUTOMATIC);

        m_VBox.pack_start(m_ScrolledWindow,true,true);
        m_VBox.pack_start(m_CtrlSep,false,false);
        m_VBox.pack_start(m_ButtonBox,false,false);

        m_ButtonBox.pack_start(m_Status_Label,true,true,3);
        m_ButtonBox.set_child_secondary(m_Status_Label,true);

        m_ButtonBox.pack_start(m_Button_Cancel, Gtk::PACK_SHRINK);
        m_ButtonBox.pack_start(m_Button_Select, Gtk::PACK_SHRINK);
        m_ButtonBox.set_border_width(5);
        m_ButtonBox.set_layout(Gtk::BUTTONBOX_END);

        // Signals
        m_Button_Cancel.signal_clicked().connect(sigc::mem_fun(*this,&View::on_button_cancel));
        m_Button_Select.signal_clicked().connect(sigc::mem_fun(*this,&View::on_button_select));

        //Create the Tree model:
        m_refTreeModel = Gtk::ListStore::create(m_Columns);
        m_TreeView.set_model(m_refTreeModel);

        m_TreeView.append_column("IP",   m_Columns.m_col_ip);
        m_TreeView.append_column("Host", m_Columns.m_col_hostname);
        m_TreeView.append_column("Name", m_Columns.m_col_name);
        m_TreeView.append_column("Port", m_Columns.m_col_port);

        show_all_children();
    }

/// Event Callbacks ////

    void View::on_button_cancel(void)
    {
        hide();
    }

    void View::on_button_select(void)
    {
        Glib::RefPtr<Gtk::TreeSelection> refTreeSelection = m_TreeView.get_selection();
        Gtk::TreeModel::iterator iter = refTreeSelection->get_selected();
        if(iter)
        {
            Gtk::TreeModel::Row row = *iter;
            signal_select.emit(
                row[m_Columns.m_col_ip],
                row[m_Columns.m_col_hostname],
                row[m_Columns.m_col_name],
                row[m_Columns.m_col_port]);
        }
        hide();
    }

/// User functions ///

    /* Delete a certain IP */
    void View::server_append(const char * ip, const char * hostname, const char * name, unsigned int port)
    {
        Gtk::TreeModel::Row row = *(m_refTreeModel->append());

        /* Fill in data */
        row[m_Columns.m_col_ip] = ip;
        row[m_Columns.m_col_hostname] = hostname;
        row[m_Columns.m_col_name] = name;
        row[m_Columns.m_col_port] = port;

        /* Autoselect current row */
        Glib::RefPtr<Gtk::TreeSelection> refTreeSelection = m_TreeView.get_selection();
        refTreeSelection->select(row);
    }

    /* Delete a certain IP */
    void View::server_delete(const char * name)
    {
        Gtk::TreeNodeChildren children = m_refTreeModel->children();
        for (Gtk::TreeIter iter = children.begin(); iter != children.end(); ++iter)
        {
            /* Compare the two strings */
            Gtk::TreeRow row = *iter;
            if(row[m_Columns.m_col_name] == name)
            {
                m_refTreeModel->erase(iter);
                break;
            }
        }
    }

    /* Set status label */
    void View::set_status(const char * message)
    {
        m_Status_Label.set_text(message);
    }
}
