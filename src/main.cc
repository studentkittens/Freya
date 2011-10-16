#include "MPDClient.hpp"
#include "IdleListener.hpp"

//--------------------------------------
//--------------------------------------

int main(int argc, char *argv[])
{
    MPDClient freya;
    freya.connect();
    
    /* Start listening to events */
    GMainLoop * main_loop = g_main_loop_new(NULL,false);
    g_main_loop_run(main_loop);
    g_main_loop_unref(main_loop);
    main_loop = NULL;

    return EXIT_SUCCESS;
}

//--------------------------------------
