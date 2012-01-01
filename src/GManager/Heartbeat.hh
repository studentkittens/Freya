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
#include "../MPD/AbstractClientUser.hh"

/**
 * @brief The prototype for the heartbeat signal
 */
typedef sigc::signal<void,double> TimerNotifier;

namespace GManager
{
    /**
     * @brief A software clock that emits a signal every 500ms
     *
     * It is used for all classes that need to show the current time,
     * Freya does not requery the MPD Status like other clients do.
     */
    class Heartbeat : public MPD::AbstractClientUser
    {
        public:

            Heartbeat(MPD::Client& client);
            ~Heartbeat(void);
            /**
             * @brief Register to the hearbeat signal
             *
             * The prototype is void on_heartbeat(double time)
             *
             * @return A sigc::connection, call connect() on it 
             */
            TimerNotifier& signal_client_update(void); 
           
            /**
             * @brief Start incrementing
             */
            void play(void); 
            /**
             * @brief Pause incrementing
             */
            void pause(void);
            /**
             * @brief Reset value to 0
             */
            void reset(void);
            /**
             * @brief Set the current value
             *
             * @param val
             */
            void set(double val);
            /**
             * @brief Get the current value
             *
             * @return 
             */
            double get(void);

        private:

            double timer;
            bool count_up;

            gboolean on_interval(void);
            TimerNotifier signal_proxy;

            void on_client_update(enum mpd_idle event, MPD::NotifyData& data);
            void on_connection_change(bool server_changed, bool is_connected);

            MPD::NotifyData * mp_LastNotifyData;
    };
}

#endif
