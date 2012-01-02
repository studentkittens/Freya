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
#include "PlaylistManagerPopup.hh"

namespace Browser
{
    static Glib::ustring pl_ui_info =
        "<ui>"
        "  <popup name='PlaylistmanagerPopupMenu'>"
        "    <menuitem action='pl_append'/>"
        "    <menuitem action='pl_replace'/>"
        "    <separator />"
        "    <menuitem action='pl_delete'/>"
        "    <separator />"
        "  </popup>"
        "</ui>";

    PlaylistManagerPopup::PlaylistManagerPopup(Gtk::Widget& to_register) : BasePopup(&to_register,pl_ui_info)
    {
        menu_add_item(m_ActionAdd,"pl_append","Append","Append to Queue",Gtk::Stock::ADD);
        menu_add_item(m_ActionRepl,"pl_replace","Replace","Replace Queue contents",Gtk::Stock::JUMP_TO);
        menu_add_item(m_ActionDel,"pl_delete","Remove Playlist","Remove this Playlist",Gtk::Stock::DELETE);
        menu_construct("PlaylistmanagerPopupMenu");
    }
}
