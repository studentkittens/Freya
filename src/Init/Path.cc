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
#include "Path.hh"

#include "../Config/defaultcfg.inl"

#include <unistd.h>
#include <string.h>
#include <glib/gstdio.h>
#include <glyr/cache.h>

namespace Init
{
Path::Path()
{
    Glib::ustring cfg_dir = get_config_dir();
    create_dir_if_missing(cfg_dir);

    Glib::ustring cache_dir = get_cache_dir();
    create_dir_if_missing(cache_dir);
}

/* return config dir path as ustring */
Glib::ustring Path::get_config_dir()
{
    return Glib::ustring(g_get_user_config_dir()) + G_DIR_SEPARATOR_S + "freya";
}

Glib::ustring Path::get_cache_dir()
{
    return Glib::ustring(g_get_user_cache_dir()) + G_DIR_SEPARATOR_S + "freya";
}

/* return path to config */
Glib::ustring Path::path_to_config()
{
    return Glib::ustring(get_config_dir()) + G_DIR_SEPARATOR_S + "config.xml";
}

/* return path to log */
Glib::ustring Path::path_to_log()
{
    return Glib::ustring(get_config_dir()) + G_DIR_SEPARATOR_S + "log.txt";
}

Glib::ustring Path::path_to_metadata_db()
{
    return Glib::ustring(get_config_dir()) + G_DIR_SEPARATOR_S + GLYR_DB_FILENAME;
}

Glib::ustring Path::path_to_css()
{
    return Glib::ustring(get_config_dir()) + G_DIR_SEPARATOR_S + "style.css";
}

/*check if config dir an file is avaiable, if not, try to create */
void Path::create_dir_if_missing(Glib::ustring& dir)
{
    const char * cdir = dir.c_str();
    if(!(g_file_test(cdir, G_FILE_TEST_EXISTS) && g_file_test(cdir, G_FILE_TEST_IS_DIR)))
    {
        create_dir(dir);
    }
}


void Path::create_file_if_missing(Glib::ustring& file, const char * content, gsize len)
{
    if(g_file_test(file.c_str(),G_FILE_TEST_IS_REGULAR))
        return;

    FILE * fHandle = fopen(file.c_str(), "w");
    if(NULL != fHandle && NULL != content)
    {
        fwrite(content, 1, len, fHandle);
        fclose(fHandle);
        g_message("config %s created.", file.c_str());
    }
    else
    {
        g_warning("unable to write %s.",file.c_str());
    }
}


/* creates dir for config.xml */
void Path::create_dir(Glib::ustring& dir)
{
    if(!g_mkdir_with_parents(dir.c_str(),0755))
    {
        g_message("dir %s, succesfully created.",dir.c_str());
    }
    else
    {
        g_warning("cannot create %s: %s",dir.c_str(),strerror(errno));
    }
}
}

