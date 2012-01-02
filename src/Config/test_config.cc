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
#include <iostream>
#include <glibmm.h>
#include <cstring>
#include "Handler.hh"

using namespace std;

/*
 * Exammple:
 * ./bin/test_config get settings.notify.signal
 * ./bin/test_config set settings.notify.signal 2
 */

int main(int argc, char *argv[])
{
    if(argc > 3 && !strcmp(argv[1],"set"))
    {
        CONFIG_SET(argv[2],argv[3]);
        int bla  = CONFIG_GET_AS_INT(Glib::ustring(argv[2]));
        g_message("value = '%d'",bla);
    }
    else if(argc > 2 && !strcmp(argv[1],"get"))
    {
        Glib::ustring bla  = CONFIG_GET(Glib::ustring(argv[2]));
        g_message("value = '%s'",bla.c_str());
    }
    else if(argc > 2 && !strcmp(argv[1],"set"))
    {
        CONFIG_SET(argv[2],argv[3]);
        Glib::ustring bla  = CONFIG_GET(Glib::ustring(argv[2]));
        g_message("value = '%s'",bla.c_str());
    }

    return EXIT_SUCCESS;
}
