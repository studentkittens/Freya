#include "Client.hh"
#include "Listener.hh"
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
        case 'n':
            {
                client->send_command("next"); 
                break;
            }
        case 'x':
            {
                client->send_command("previous");
                break;
            }
        case 's':
            {
                client->send_command("stop");
                break;
            }
        case 'p':
            {
                client->send_command("play");
                break;
            }
        case '#':
            {
                client->play_song_at_id(2);
                break;
            }
        case 'c':
            {
                client->connect();
                break;
            }
        case ':':
            {
                char cmd[256] = {0};
                if(fgets(cmd,255,stdin))
                {
                    char * nl = strrchr(cmd,'\n');
                    if(nl != NULL) nl[0] = 0;
                    client->send_command(cmd);
                }

                /* Do not unread newline */
                return true;
            }
        case 'd':
            {
                client->disconnect();
                break;
            }
    }

    /* Unread characters left on the stream (if any) */
    while ((c = getchar()) != EOF && c != '\n'); 
    return retv;
}

//--------------------------------------
//--------------------------------------

// Anmerkung: Das ist momentan mehr oder minder zusammen gehackter Code
// der meinen eigenen Verständniss dient - hier ist alles weit weg von
// offiziell - irgendwie muss ich mich ja mit der lib beschäftigen.

int main(int argc, char *argv[])
{
    /* TODO: This connects automagically at the moment */
    MPD::Client freya;

    /* Eventloop */
    RefPtr<MainLoop> app_loop = MainLoop::create(false);

    shell_data data;
    data.client = &freya;
    data.loop   = app_loop->gobj();

    GIOChannel * stdin_chan = g_io_channel_unix_new(fileno(stdin));
    g_io_add_watch(stdin_chan,G_IO_IN,stdin_io_callback,(gpointer)&data); 

    freya.force_update();

    /* Start listening to events */
    app_loop->run();
    app_loop->unreference();
    g_io_channel_unref(stdin_chan);

    return EXIT_SUCCESS;
}

//--------------------------------------
