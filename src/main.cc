#include "MPDClient.hpp"
#include "IdleListener.hpp"

using namespace Glib;

gboolean stdin_io(GIOChannel *source, GIOCondition condition, gpointer data)
{
    cerr << "Exiting" << endl;
    int c = 0;
    while ((c = getchar()) != EOF && c != '\n'); 
    exit(0);
    return false;
}

//--------------------------------------
//--------------------------------------

// Anmerkung: Das ist momentan mehr oder minder zusammen gehackter Code
// der meinen eigenen Verständniss dient - hier ist alles weit weg von
// offiziell - irgendwie muss ich mich ja mit der lib beschäftigen.

int main(int argc, char *argv[])
{
    /* This is already wrong. Instancing a model.. */
    MPDClient freya;
    freya.connect();

    GIOChannel * stdin_chan = g_io_channel_unix_new(fileno(stdin));
    g_io_add_watch(stdin_chan,G_IO_IN,stdin_io,NULL); 

    /* Start listening to events */
    RefPtr<MainLoop> app_loop = MainLoop::create(false);
    app_loop->run();
    app_loop->unreference();

    return EXIT_SUCCESS;
}

//--------------------------------------
