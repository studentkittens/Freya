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
#ifndef STATBROWSER_H0M8CVQP

#define STATBROWSER_H0M8CVQP

#include <gtkmm.h>
#include "../MPD/Client.hh"
#include "../Utils/Utils.hh"
#include "AbstractBrowser.hh"

namespace Browser {
    class StatBrowser : public Gtk::Frame, public AbstractBrowser {
        public:
            StatBrowser (MPD::Client&, Glib::RefPtr<Gtk::Builder>&);
            ~StatBrowser ();
            

            /**
             * @brief implemented from AbstractBrowser
             *
             * @return topcontainer of this browser
             */
            Gtk::Widget * get_container(void);

        private:
            /* label members for statistics*/
            Gtk::Label *noofartist, *noofalbums, *noofsongs, *dbplaytime, *playtime, *dbupdate, *uptime;
            void on_client_update(enum mpd_idle event, MPD::NotifyData& data);
    };
}
#endif /* end of include guard: STATBROWSER_H0M8CVQP */


