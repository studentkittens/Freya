/***********************************************************
 * This file is part of Freya
 * - A free MPD Gtk3 MPD Client -
 *
 * Authors: Christopher Pahl, Christoph Piechula,
 *          Eduard Schneider
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

#include "../../config.h"

#include "../GManager/Window.hh"
#include "../GManager/PlaybackButtons.hh"
#include "../GManager/BrowserList.hh"
#include "../GManager/Statusbar.hh"
#include "../GManager/Timeslide.hh"
#include "../GManager/TitleLabel.hh"
#include "../GManager/StatusIcons.hh"
#include "../GManager/VolumeSlider.hh"
#include "../GManager/Heartbeat.hh"
#include "../GManager/MenuList.hh"
#include "../GManager/Trayicon.hh"

#include "../Browser/Queue/Queue.hh"
#include "../Browser/PlaylistManager/PlaylistManager.hh"
#include "../Browser/Database/Database.hh"
#include "../Browser/Statistics/StatBrowser.hh"
#include "../Browser/Settings/Settings.hh"

#include "../Log/Writer.hh"
#include "../Utils/Utils.hh"
#include "SignalHandler.hh"
#include "CssLoader.hh"

#if USE_LIBNOTIFY
    #include "../GManager/NotifyManager.hh"
#endif

#if USE_AVAHI
    #include "../Browser/Avahi/ServerList.hh"
#endif

#if USE_GLYR
    #include "../Browser/NowPlaying/NowPlaying.hh"
    #include "../Glyr/Request.hh"
#endif 


////////////////////////

int main(int argc, char *argv[])
{
    Glib::thread_init(NULL);
    setlocale(LC_ALL,"");

    Gtk::Main kit(argc,argv);

    try
    {
        /* Check if debug output enabled */
        if(argc > 1 && !strcmp("-v",argv[1]))
            LogSetVerbosity(Log::LOG_DEBUG);
        else
            LogSetVerbosity(Log::LOG_INFO);

#if USE_GLYR
        /* Metadata System */
        Glyr::Stack::instance();
#endif

        /* Register fatal signals like SIGSEGV */
        Init::SignalHandler sig_handler;

        /* TODO: Play a bit around with prealloc() */
        MPD::Song::prealloc(10000);
        atexit(MPD::Song::disposeAll);

        /* Instance the client */
        MPD::Client client;

        /* Try to laod the css file */
        Init::CssLoader css;

        /* Get the glade file */
        Glib::RefPtr<Gtk::Builder> builder = Gtk::Builder::create();
        BUILDER_ADD(builder,"ui/Freya.glade");

        /* Instanmce gui elements */
        GManager::Window main_window(builder);
        GManager::Heartbeat proxy(client);
        GManager::Timeslide timeslide(proxy,client,builder);
        GManager::VolumeSlider vol_button(client,builder);
        GManager::Statusbar statusbar(proxy,client,builder);
        GManager::PlaybackButtons buttons(client,builder);
        GManager::TitleLabel title_label(client,builder);
        GManager::Statusicons status_icons(client,builder);
        GManager::MenuList menu_list(client,builder);
        GManager::Trayicon tray(client,*main_window.get_window());

#if USE_LIBNOTIFY
        GManager::NotifyManager notify_mgr(client);
#endif

        GManager::BrowserList browser_list(client,builder);

        /* Instance browsers */

#if USE_GLYR
        Browser::NowPlaying np_browser(client,builder,browser_list);
        browser_list.add(np_browser);
#endif

        Browser::Queue queue_browser(client,builder,browser_list);
        browser_list.add(queue_browser);

        Browser::PlaylistManager playlists_browser(client,builder,browser_list);
        browser_list.add(playlists_browser);

        Browser::Database db_browser(client,builder,browser_list);
        browser_list.add(db_browser);

        Browser::StatBrowser stat_browser(client,builder,browser_list);
        browser_list.add(stat_browser);

        Browser::Settings settings_browser(client,builder,&tray,browser_list);
        browser_list.add(settings_browser);

#if USE_AVAHI    
        Browser::ServerList server_list(builder,browser_list);
        browser_list.add(server_list);
#endif

        browser_list.set(queue_browser);

        main_window.get_window()->show();

        Debug("Setting up GUI done.");

        ///////////////////

        /* Send a good morning to all widgets */
        if(CONFIG_GET_AS_INT("settings.connection.autoconnect"))
        {
            client.connect();
        }

        /* ------START -------- */

        Debug("Entering Mainloop!");

        kit.run();

        /*------ END ---------- */

        if(CONFIG_GET_AS_INT("settings.playback.stoponexit"))
        {
            client.playback_stop();
        }

#if USE_GLYR
        // Do this before disconnecting, since it may take some time.
        Glyr::Stack::instance().destroy();
#endif

        client.disconnect();
    }
    catch(const Gtk::BuilderError& e)
    {
        Critical("BuilderError: %s",e.what().c_str());
    }
    catch(const Glib::FileError& e)
    {
        Critical("General Uncaught Exception: %s",e.what().c_str());
    }
    return EXIT_SUCCESS;
}
