#include "GManager/PlaylistTreeView.hh"
#include "GManager/PlaybackButtons.hh"
#include "GManager/BrowserList.hh"
#include "GManager/Statusbar.hh"
#include "GManager/Timeslide.hh"
#include "GManager/TitleLabel.hh"
#include "GManager/StatusIcons.hh"
#include "MPD/Client.hh"

using namespace std;

void notify(enum mpd_idle, MPD::NotifyData& data)
{
    cerr << "View observer was told to update." << endl;
}

int main(int argc, char *argv[])
{
    Gtk::Main kit(argc,argv);
    try
    {
        MPD::Client client;

        Glib::RefPtr<Gtk::Builder> builder = Gtk::Builder::create_from_file("ui/Freya.glade");
        GManager::PlaylistTreeView playlist_queue(builder);
        GManager::Timeslide timeslide(builder);
        GManager::Statusbar statusbar(client,builder);
        GManager::BrowserList browser_list(builder);
        GManager::PlaybackButtons buttons(client,builder);
        GManager::TitleLabel title_label(client,builder);
        GManager::Statusicons status_icons(client,builder);

        // Silly test
        client.get_notify().connect(sigc::ptr_fun(notify));

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
