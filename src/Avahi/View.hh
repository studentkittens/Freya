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
#ifndef FREYA_AVAHIVIEW_H
#define FREYA_AVAHIVIEW_H

#include <gtkmm.h>

namespace Avahi
{
    /**
     * @brief Representation of the Avahi::Browser, do not use this yourself
     */
    class View : public Gtk::Window
    {
    public:
        View(void);

        /**
         * @brief Append a new server to the View
         *
         * @param ip the ip field
         * @param hostname the hostname
         * @param name server name (chosen by the admin)
         * @param port The port we'd onnect to
         */
        void server_append(const char * ip, const char * hostname, const char * name, unsigned int port);
        /**
         * @brief Delete a server by it's name
         *
         * @param name the name of the server (which is hopefully unique)
         */
        void server_delete(const char * name);
        /**
         * @brief Set the status label
         *
         * @param message
         */
        void set_status(const char * message);

        /* Select callback */
        sigc::signal<void,Glib::ustring,Glib::ustring,Glib::ustring, unsigned int> signal_select;

    protected:
        //Signal handlers:
        void on_button_cancel();
        void on_button_select();

        //Tree model columns:
        class ModelColumns : public Gtk::TreeModel::ColumnRecord
        {
        public:

            ModelColumns()
            {
                add(m_col_ip);
                add(m_col_hostname);
                add(m_col_name);
                add(m_col_port);
            }

            Gtk::TreeModelColumn<Glib::ustring> m_col_ip;
            Gtk::TreeModelColumn<Glib::ustring> m_col_hostname;
            Gtk::TreeModelColumn<Glib::ustring> m_col_name;
            Gtk::TreeModelColumn<unsigned int>  m_col_port;
        };

        ModelColumns m_Columns;

        //Child widgets:
        Gtk::VBox m_VBox;

        Gtk::ScrolledWindow m_ScrolledWindow;
        Gtk::TreeView m_TreeView;
        Glib::RefPtr<Gtk::ListStore> m_refTreeModel;

        Gtk::HButtonBox m_ButtonBox;
        Gtk::Button m_Button_Cancel;
        Gtk::Button m_Button_Select;
        Gtk::Label  m_Status_Label;
        Gtk::Separator m_CtrlSep;
    };
}
#endif //GTKMM_View_H
