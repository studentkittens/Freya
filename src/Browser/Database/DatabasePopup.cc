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
#include "DatabasePopup.hh"

namespace Browser
{
    static Glib::ustring ui_info =
        "<ui>"
        "  <popup name='DatabasePopupMenu'>"
        "    <menuitem action='db_add'/>"
        "    <menuitem action='db_add_all'/>"
        "    <separator />"
        "    <menuitem action='db_replace'/>"
        "    <separator />"
        "    <menuitem action='db_update'/>"
        "    <menuitem action='db_rescan'/>"
        "  </popup>"
        "</ui>";

    DatabasePopup::DatabasePopup(Gtk::Widget& to_register) : BasePopup(&to_register,ui_info)
    {
        menu_add_item(m_ActionAdd,"db_add","Add","Add to Queue",Gtk::Stock::ADD);
        menu_add_item(m_ActionAddAll,"db_add_all","Add All","Add Everything",Gtk::Stock::ADD);
        menu_add_item(m_ActionReplace,"db_replace","Replace","remove selected playlists",Gtk::Stock::JUMP_TO);
        menu_add_item(m_ActionUpdate,"db_update","Update","Update database",Gtk::Stock::REFRESH);
        menu_add_item(m_ActionRescan,"db_rescan","Rescan","Rescan database",Gtk::Stock::REFRESH);
        menu_construct("DatabasePopupMenu");
    }
}
