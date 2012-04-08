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
#include "Client.hh"
#include "../Log/Writer.hh"
#include <cstring>

using namespace MPD;

/////////////////////////////////
/////////////////////////////////

int main(int argc, char *argv[])
{
    LogSetVerbosity(Log::LOG_CRITICAL);
    setlocale(LC_ALL,"");
    Glib::Timer watch;
    watch.stop();
    if(argc > 3)
    {
        Client freya;
        Query * query = NULL;
        freya.connect();
        if(strcasecmp(argv[1],"songs") == 0)
        {
            query = freya.create_db_songs_query();
            std::vector<MPD::Song*> songlist;
            for(int i = 2; i < argc; i += 2)
            {
                query->add_tag_constraint(argv[i],argv[i+1]);
            }
            watch.start();
            query->commit(songlist);
            watch.stop();
            for(std::vector<MPD::Song*>::iterator it = songlist.begin(); it != songlist.end(); it++)
            {
                g_print("%s\n",(*it)->get_path());
                delete *it;
            }
            delete query;
        }
        else if(strcasecmp(argv[1],"tags") == 0)
        {
            mpd_tag_type tag = mpd_tag_name_iparse(argv[2]);
            query = freya.create_db_tag_query(tag);
            std::vector<char *> taglist;
            for(int i = 3; i < argc; i += 2)
            {
                query->add_tag_constraint(argv[i],argv[i+1]);
            }
            watch.start();
            query->commit(taglist);
            watch.stop();
            for(std::vector<char*>::iterator it = taglist.begin(); it != taglist.end(); it++)
            {
                g_print("%s\n",(*it));
                g_free((*it));
            }
            delete query;
        }
    }
    g_printerr("%lf\n",watch.elapsed());
    return EXIT_SUCCESS;
}

/////////////////////////////////-------
