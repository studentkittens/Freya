#include "MPD/Client.hh"

#include "GManager/PlaybackButtons.hh"
#include "GManager/BrowserList.hh"
#include "GManager/Statusbar.hh"
#include "GManager/Timeslide.hh"
#include "GManager/TitleLabel.hh"
#include "GManager/StatusIcons.hh"
#include "GManager/Volumebutton.hh"
#include "GManager/ClientTimerProxy.hh"

#include "Browser/PlaylistTreeView.hh"

using namespace std;

int main(int argc, char *argv[])
{
    Gtk::Main kit(argc,argv);
    try
    {
        /* Instance the client */
        MPD::Client client;

        /* Get the glade file */
        Glib::RefPtr<Gtk::Builder> builder = Gtk::Builder::create_from_file("ui/Freya.glade");

        /* Instanmce gui elements */
        GManager::ClientTimerProxy proxy; 
        GManager::Timeslide timeslide(proxy,client,builder);
        GManager::Statusbar statusbar(proxy,client,builder);
        GManager::PlaybackButtons buttons(client,builder);
        GManager::TitleLabel title_label(client,builder);
        GManager::Statusicons status_icons(client,builder);
        GManager::Volumebutton vol_button(client,builder);
        GManager::BrowserList browser_list(builder);

        /* Instance browser  */
        Browser::PlaylistTreeView playlist_queue(client);
        browser_list.add(playlist_queue);

        /* Send a good morning to all widgets */
        client.force_update();

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
