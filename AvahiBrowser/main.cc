#include "AvahiHandler.hh"
#include <gtkmm/main.h>

int main (int argc, char *argv[])
{
    Gtk::Main kit(argc, argv);

    /* Build Handler */
    FreyaAvahiHandler handle;

    /* Start the GLIB Main Loop */
    Gtk::Main::run(handle.get_window());

    /* Goodbye */
    return EXIT_SUCCESS;
}
