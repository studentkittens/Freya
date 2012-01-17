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

#ifndef FREYA_DEFAULTCFG_QANZVJMD
#define FREYA_DEFAULTCFG_QANZVJMD
#include <glibmm/ustring.h>

namespace Config
{
    static const Glib::ustring defaultconfig(
            "<?xml version=\"1.0\" encoding=\"utf-8\"?>\n"
            "<freya>\n"
            "    <settings>\n"
            "        <connection>\n"
            "            <port>6600</port>\n"
            "            <musicroot>~/chris/Musik</musicroot>\n"
            "            <host>localhost</host>\n"
            "            <!-- Connect on startup? -->\n"
            "            <autoconnect>1</autoconnect>\n"
            "            <!-- In seconds -->\n"
            "            <timeout>20</timeout>\n"
            "             <!-- Autoreconnect interval in seconds -->\n"
            "            <reconnectinterval>2</reconnectinterval>\n"
            "        </connection>\n"
            "        <libnotify>\n"
            "           <!-- Show notifications? -->\n"
            "            <signal>0</signal>\n"
            "           <!-- How long? -->\n"
            "            <timeout>-1</timeout>\n"
            "        </libnotify>\n"
            "        <trayicon>\n"
            "            <!-- Show trayicon? -->\n"
            "            <tray>0</tray>\n"
            "            <!-- To tray when closing? -->\n"
            "            <totrayonclose>0</totrayonclose>\n"
            "        </trayicon>\n"
            "        <playback>\n"
            "            <!-- Stop music when closing Freya? -->\n"
            "            <stoponexit>0</stoponexit>\n"
            "        </playback>\n"
            "    </settings>\n"
            "    <plugins>\n"
            "    </plugins>\n"
            "</freya>\n"
            );
}

#endif /* end of include guard: DEFAULTCFG_QANZVJMD */
