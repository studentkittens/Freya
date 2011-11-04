#include <gtkmm.h>

int main(int argc, char *argv[])
{
    Gtk::Main gtk_main(argc,argv);
    Glib::RefPtr<Gtk::Builder> builder = Gtk:: Builder::create_from_file("Mockup_eddy.glade");

    Gtk::Window* main_window;
    builder->get_widget("MainWindow", main_window);
    gtk_main.run(*main_window);


    return 0;
}
