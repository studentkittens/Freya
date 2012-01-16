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
#include "Browser.hh"
#include "../Config/Handler.hh"
#include <gtkmm/main.h>
#include <iostream>

using namespace std;

void selected_callback(Glib::ustring ip,Glib::ustring hostname,Glib::ustring name, unsigned int port)
{
    CONFIG_SET("settings.connection.host",ip);
    CONFIG_SET_AS_INT("settings.connection.port",port);
    cerr << ip << endl << hostname << endl << name << endl << port << endl;
}

int main (int argc, char *argv[])
{
    Gtk::Main kit(argc, argv);

    /* Build Browser */
    Avahi::Browser handle;

    if(handle.is_connected())
    {
        handle.signal_selection_done().connect(sigc::ptr_fun(selected_callback));

        /* Start the GLIB Main Loop */
        Gtk::Main::run(handle.get_window());
    }

    /* Goodbye */
    return EXIT_SUCCESS;
}
