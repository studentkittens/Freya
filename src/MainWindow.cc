#include <gtkmm.h>
#include <stdlib.h>
#include <iostream>

#include "PlaylistTreeView.hh"
#include "PlaybackButtons.hh"
#include "BrowserList.hh"
#include "Statusbar.hh"
#include "Timeslide.hh"

#include "MPD/Client.hh"

using namespace std;

void notify(enum mpd_idle, mpd_status * status)
{
    cerr << "Cool." << endl;
}

int main(int argc, char *argv[])
{
    Gtk::Main kit(argc,argv);
    try
    {
        MPD::Client client;

        Glib::RefPtr<Gtk::Builder> builder = Gtk::Builder::create_from_file("ui/Freya.glade");
        GuiLogic::PlaylistTreeView playlist_queue(builder);
        GuiLogic::Timeslide timeslide(builder);
        GuiLogic::Statusbar statusbar(builder);
        GuiLogic::BrowserList browser_list(builder);
        GuiLogic::PlaybackButtons buttons(&client,builder);

        // Silly test
        client.get_notify()->connect(sigc::ptr_fun(notify));

        Gtk::Window * main_window = NULL;
        builder->get_widget("FreyaMainWindow", main_window);
        kit.run(*main_window);
    }
    catch(const Gtk::BuilderError& e)
    {
        std::cerr << "BuilderError: " << e.what() << std::endl;
    }
    catch(const Glib::FileError& e)
    {
        std::cerr << "General exception: " << e.what() << std::endl;
    }

    return EXIT_SUCCESS;
}

