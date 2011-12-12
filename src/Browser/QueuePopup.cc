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
#include "QueuePopup.hh"

namespace Browser
{
    static Glib::ustring ui_info =
        "<ui>"
        "  <popup name='QueuePopupMenu'>"
        "    <menuitem action='q_remove'/>"
        "    <menuitem action='q_clear'/>"
        "    <separator />"
        "    <menuitem action='q_add_as_pl'/>"
        "  </popup>"
        "</ui>";

    QueuePopup::QueuePopup(Gtk::Widget& to_register) : BasePopup(&to_register,ui_info)
    {
        menu_add_item(m_ActionDel,"q_remove","Remove","Remove selected Songs",Gtk::Stock::DELETE);
        menu_add_item(m_ActionDel,"q_add_as_pl","Save as Playlist","Save current queue as a playlist",Gtk::Stock::JUMP_TO);
        menu_add_item(m_ActionClear,"q_clear","Clear","Clear Queue",Gtk::Stock::CLEAR);
        menu_construct("QueuePopupMenu");
    }
}
