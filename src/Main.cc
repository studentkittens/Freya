#include "MPD/Client.hh"
#include "FreyaWindow.hh"

#include "GManager/PlaybackButtons.hh"
#include "GManager/BrowserList.hh"
#include "GManager/Statusbar.hh"
#include "GManager/Timeslide.hh"
#include "GManager/TitleLabel.hh"
#include "GManager/StatusIcons.hh"
#include "GManager/Volumebutton.hh"
#include "GManager/Heartbeat.hh"
#include "GManager/MenuList.hh"
#include "GManager/NotifyManager.hh"
#include "GManager/Trayicon.hh"
#include "GManager/DisconnectManager.hh"

#include "Browser/Queue.hh"
#include "Browser/PlaylistManager.hh"
#include "Browser/Database.hh"
#include "Browser/StatBrowser.hh"
#include "Browser/Settings.hh"
#include "Log/Writer.hh"

#include "Utils/Utils.hh"

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

        FreyaWindow main_window(builder);

        /* Instanmce gui elements */
        GManager::Heartbeat proxy(client);
        GManager::Timeslide timeslide(proxy,client,builder);
        GManager::Statusbar statusbar(proxy,client,builder);
        GManager::PlaybackButtons buttons(client,builder);
        GManager::TitleLabel title_label(client,builder);
        GManager::Statusicons status_icons(client,builder);
        GManager::Volumebutton vol_button(client,builder);
        GManager::BrowserList browser_list(client,builder);
        GManager::MenuList menu_list(client,builder);
        GManager::Trayicon tray(client,*main_window.get_window());
        GManager::NotifyManager notify_mgr(client);

        /* Instance browser  */
        Browser::Queue queue_browser(client,builder);
        browser_list.add(queue_browser);

        Browser::PlaylistManager playlists_browser(client,builder);
        browser_list.add(playlists_browser);

        Browser::DatabaseBrowser db_browser(client,builder);
        browser_list.add(db_browser);

        Browser::StatBrowser stat_browser(client,builder);
        browser_list.add(stat_browser);

        Browser::Settings settings_browser(builder,&tray);
        browser_list.add(settings_browser);

        /* Send a good morning to all widgets */
        client.force_update();

        /* Instance after being connected (usually) */
        GManager::DisconnectManager(client,main_window.get_window(),builder);

        main_window.get_window()->show();
        kit.run();
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
