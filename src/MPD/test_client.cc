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
#include "Client.hh"
#include "../Log/Writer.hh"

#include <cstring>

using namespace Glib;
using namespace MPD;

typedef struct
{
    MPD::Client * client;
    GMainLoop * loop;

} shell_data;


gboolean stdin_io_callback(GIOChannel *source, GIOCondition condition, gpointer data)
{
    gboolean  retv = true;

    shell_data * watch_data = (shell_data *)data;
    GMainLoop * main_loop = watch_data->loop;
    MPD::Client * client = watch_data->client;

    int c = getchar();
    switch(c)
    {
        case 'q': 
            {
                /* Quit mainloop */
                g_main_loop_ref(main_loop);
                g_main_loop_quit(main_loop);
                retv = false;
                break;
            }
        case ':':
            {
                char cmd[256] = {0};
                if(fgets(cmd,255,stdin))
                {
                    /* Chomp newline */
                    char * nl = strrchr(cmd,'\n');
                    if(nl != NULL) nl[0] = 0;
                    client->send_command(cmd);
                }

                /* Do not unread newline */
                return true;
            }
        default:
            {
                break;
            }
    }

    /* Unread characters left on the stream (if any) */
    while ((c = getchar()) != EOF && c != '\n'); 

    return retv;
}

//--------------------------------------
//--------------------------------------

int main(int argc, char *argv[])
{
    MPD::Client freya;

    /* Eventloop */
    RefPtr<MainLoop> app_loop = MainLoop::create(false);

    shell_data data;
    data.client = &freya;
    data.loop   = app_loop->gobj();

    GIOChannel * stdin_chan = g_io_channel_unix_new(fileno(stdin));
    g_io_add_watch(stdin_chan,G_IO_IN,stdin_io_callback,(gpointer)&data); 

    freya.connect();

    Info("Enter your command prepended with a ':'");
    Info("Example: :status or :next");
    Info("Type 'q' to quit.");

    /* Start listening to events */
    app_loop->run();
    app_loop->unreference();
    g_io_channel_unref(stdin_chan);

    return EXIT_SUCCESS;
}

//--------------------------------------
