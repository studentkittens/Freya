#include "AvahiHandler.hh"
#include <gtkmm/main.h>
#include <iostream>

using namespace std;

void selected_callback(Glib::ustring ip,Glib::ustring hostname,Glib::ustring name, unsigned int port)
{
    cerr << ip << endl << hostname << endl << name << endl << port << endl;
}

int main (int argc, char *argv[])
{
    Gtk::Main kit(argc, argv);

    /* Build Handler */
    FreyaAvahiHandler handle;

    if(handle.is_connected())
    {
        handle.get_signal().connect(sigc::ptr_fun(selected_callback));

        /* Start the GLIB Main Loop */
        Gtk::Main::run(handle.get_window());
    }

    /* Goodbye */
    return EXIT_SUCCESS;
}
