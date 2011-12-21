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
#include <stdio.h>
#include <glib.h>
#include <stdlib.h>
#include "init.hh"

init::init()
{}

init::~init()
{}

Glib::ustring init::get_config_dir()
{
    Glib::ustring retv = g_strdup_printf("%s%s",g_get_user_config_dir(),"/freya");
    printf("%s\n",retv.c_str());
    return retv;
}


void init::dir_is_avaiable()
{

    if (g_file_test(get_config_dir().c_str(), G_FILE_TEST_EXISTS ))
        printf("ja es ist da\n");
    else
    {
        printf("nein es ist nicht da\n");
        create_dir();
    }
}

void init::create_dir()
{
    g_mkdir(get_config_dir().c_str(),0755);
}

