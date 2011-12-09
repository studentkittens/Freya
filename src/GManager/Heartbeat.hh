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
#ifndef FREYA_HEARTBEAT_GUARD
#define FREYA_HEARTBEAT_GUARD

#include "../MPD/Client.hh"
#include "../AbstractClientUser.hh"

/* Explanation:
 * This class listens on the Client to get player signals, 
 * additionally it emits a signal every 500ms, for widgets
 * like the statusbar. In short: it is some sort of signalproxy
 */

typedef sigc::signal<void,double> TimerNotifier;

namespace GManager
{
    class Heartbeat : public AbstractClientUser
    {
        public:

            Heartbeat(MPD::Client& client);
            ~Heartbeat(void);
            TimerNotifier& get_notify(void); 
           
            void play(void); 
            void pause(void);
            void reset(void);
            void set(double val);
            double get(void);

        private:

            double timer;
            bool count_up;

            gboolean on_interval(void);
            TimerNotifier signal_proxy;

            void on_client_update(enum mpd_idle event, MPD::NotifyData& data);
            void on_connection_change(bool is_connected);
    };
}

#endif
