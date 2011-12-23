/***********************************************************
 * This file is part of Freya 
 * - A free MPD Gtk3 MPD Client -
 * 
 * Authors: Christopher Pahl, Christoph Piechula,
 *          Eduard Schneider, Marc Tigges
 *
 * Copyright (C) [2011-2012]
 * Hosted at: https://github.com/studentkittens/Freya
 *
 *              __..--''``---....___   _..._    __
 *    /// //_.-'    .-/";  `        ``<._  ``.''_ `. / // /
 *   ///_.-' _..--.'_                        `( ) ) // //
 *   / (_..-' // (< _     ;_..__               ; `' / ///
 *    / // // //  `-._,_)' // / ``--...____..-' /// / //  
 *  Ascii-Art by Felix Lee <flee@cse.psu.edu>
 *
 * Freya is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * Freya is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with Freya. If not, see <http://www.gnu.org/licenses/>.
 **************************************************************/
#include "../MPD/Client.hh"

#include "../GManager/Window.hh"
#include "../GManager/PlaybackButtons.hh"
#include "../GManager/BrowserList.hh"
#include "../GManager/Statusbar.hh"
#include "../GManager/Timeslide.hh"
#include "../GManager/TitleLabel.hh"
#include "../GManager/StatusIcons.hh"
#include "../GManager/Volumebutton.hh"
#include "../GManager/Heartbeat.hh"
#include "../GManager/MenuList.hh"
#include "../GManager/NotifyManager.hh"
#include "../GManager/Trayicon.hh"

#include "../Browser/Queue/Queue.hh"
#include "../Browser/PlaylistManager/PlaylistManager.hh"
#include "../Browser/Database/Database.hh"
#include "../Browser/Statistics/StatBrowser.hh"
#include "../Browser/Settings/Settings.hh"
#include "../Browser/Fortuna/Fortuna.hh"
#include "../Log/Writer.hh"

#include "../Utils/Utils.hh"

#include "SignalHandler.hh"

using namespace std;

int main(int argc, char *argv[])
{
    Gtk::Main kit(argc,argv);

    try
    {
        /* Register fatal signals like SIGSEGV */
        Init::SignalHandler sig_handler;

        /* Instance the client */
        MPD::Client client;

        /* Get the glade file */
        Glib::RefPtr<Gtk::Builder> builder = Gtk::Builder::create_from_file("ui/Freya.glade");

        GManager::Window main_window(builder);

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

        Browser::Database db_browser(client,builder);
        browser_list.add(db_browser);

        Browser::StatBrowser stat_browser(client,builder);
        browser_list.add(stat_browser);

        Browser::Settings settings_browser(client,builder,&tray);
        browser_list.add(settings_browser);

        Browser::Fortuna easter_egg(builder);
        browser_list.set(easter_egg);

        /* Send a good morning to all widgets */
        client.connect();

        main_window.get_window()->show();

        /* ------START -------- */

        kit.run();

        /*------ END ---------- */ 

        if(CONFIG_GET_AS_INT("settings.playback.stoponexit"))
        {
            client.playback_stop();
        }

        client.disconnect();
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
