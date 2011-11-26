#include "MPD/Client.hh"

#include "GManager/PlaybackButtons.hh"
#include "GManager/BrowserList.hh"
#include "GManager/Statusbar.hh"
#include "GManager/Timeslide.hh"
#include "GManager/TitleLabel.hh"
#include "GManager/StatusIcons.hh"
#include "GManager/Volumebutton.hh"
#include "GManager/Heartbeat.hh"
#include "GManager/MenuList.hh"

#include "Browser/PlaylistTreeView.hh"
#include "Browser/PlaylistManager.hh"
#include "Browser/Database.hh"
#include "Browser/StatBrowser.hh"
#include "Browser/Settings.hh"
#include "Log/Writer.hh"

#include "Utils/Utils.hh"

using namespace std;

class DisconnectManager
{
    public:
        DisconnectManager(MPD::Client& client, Gtk::Window * main_window, const Glib::RefPtr<Gtk::Builder> &builder)
        {
            mp_Window = main_window;
            mp_Client = &client;
            mp_Client->signal_connection_change().connect(sigc::mem_fun(*this,&DisconnectManager::on_connection_change));
            BUILDER_GET(builder,"main_paned",mp_Main_Paned);
            BUILDER_GET(builder,"top_box",mp_Top_Box);
        }

        virtual ~DisconnectManager(void) {}

    private:

        void on_connection_change(bool is_connected)
        {
            if(is_connected)
            {
                Info("Got reconnected - unlocking gui");
                mp_Main_Paned->set_sensitive(true);
                mp_Top_Box->set_sensitive(true);
                //mp_Window->set_sensitive(true);
            }
            else
            {
                Info("Got disconnected - locking gui");
                mp_Main_Paned->set_sensitive(false);
                mp_Top_Box->set_sensitive(false);
                //mp_Window->set_sensitive(false);
            }
        }

        MPD::Client * mp_Client;
        Gtk::Window * mp_Window;
        Gtk::Box * mp_Top_Box;
        Gtk::Paned * mp_Main_Paned;
};


int main(int argc, char *argv[])
{
    Gtk::Main kit(argc,argv);
    try
    {
        /* Instance the client */
        MPD::Client client;

        if(client.is_connected())
        {
            /* Get the glade file */
            Glib::RefPtr<Gtk::Builder> builder = Gtk::Builder::create_from_file("ui/Freya.glade");

            /* Instanmce gui elements */
            GManager::Heartbeat proxy(client); 
            GManager::Timeslide timeslide(proxy,client,builder);
            GManager::Statusbar statusbar(proxy,client,builder);
            GManager::PlaybackButtons buttons(client,builder);
            GManager::TitleLabel title_label(client,builder);
            GManager::Statusicons status_icons(client,builder);
            GManager::Volumebutton vol_button(client,builder);
            GManager::BrowserList browser_list(builder);
            GManager::MenuList menu_list(client,builder);

            /* Instance browser  */
            Browser::PlaylistTreeView queue_browser(client);
            browser_list.add(queue_browser);

            Browser::PlaylistManager playlists_browser(client,builder);
            browser_list.add(playlists_browser);

            Browser::DatabaseBrowser db_browser(client,builder);
            browser_list.add(db_browser);

            Browser::StatBrowser stat_browser(client,builder);
            browser_list.add(stat_browser);

            Browser::Settings settings_browser(builder);
            browser_list.add(settings_browser);

            /* Send a good morning to all widgets */
            client.force_update();

            Gtk::Window * main_window = NULL;
            builder->get_widget("FreyaMainWindow", main_window);
            DisconnectManager(client,main_window,builder);
            kit.run(*main_window);
        }
        else throw "Cannot connect to MPD Server.";
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
