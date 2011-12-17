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
#ifndef FREYA_LISTENER_GUARD
#define FREYA_LISTENER_GUARD

#include <mpd/client.h>
#include <mpd/async.h>
#include <mpd/parser.h>
#include <glibmm.h>

#include "Status.hh"
#include "NotifyData.hh"
#include "Connection.hh"

/* Typedef, so no error-prone rewriting of this sig */
typedef sigc::signal<void,enum mpd_idle, MPD::NotifyData&> EventNotifier;

namespace MPD
{
    class Listener
    {
        public:
            Listener(EventNotifier * notifier, Connection& sync_conn);
            ~Listener();

            /* Enter idle mode
             * Returns: true on success 
             */
            bool enter(void);

            /* Leave idle mode (in order to send commands)
            */
            void leave(void);

            /* Checks if connection is in idle mode
            */
            bool is_idling(void);

            //---------------//
            // Classmembers  //
            //---------------//

            NotifyData& signal_client_update_data(void);


            /**
             * @brief Emits callback forced with current data
             */
            void force_update(void); 

        private:
        
            /**
             * Utility (therefore static) function to
             * convert a GIOCondition bit mask to #mpd_async_event.
             */
            enum mpd_async_event GIOCondition_to_MPDAsyncEvent(Glib::IOCondition condition);

            //--------------------------------

            /**
             * Converts a #mpd_async_event bit mask to GIOCondition.
             */
            Glib::IOCondition MPDAsyncEvent_to_GIOCondition(enum mpd_async_event events);


            /* check if async connection is doing weird things */
            bool check_async_error(void);
            bool recv_parseable(void);
            gboolean io_callback(Glib::IOCondition condition);
            bool parse_response(char *line);
            void invoke_user_callback(void);
            void create_watch(enum mpd_async_event events);

            //-----------------//
            // Instancemembers //
            //-----------------//

            /* true if in idlemode */
            bool is_idle;

            /* True while executing leave(),
             * prevents enter() from being called
             * */
            bool is_leaving;

            /* True while callback is executed */
            bool is_working;

            /* True when a forced update was requested */
            bool is_forced;

            /* A reponse parser */
            struct mpd_parser * mp_Parser;

            /* Non blocking connection */
            struct mpd_async  * async_conn;

            /* The fd id of async_conn */
            int async_socket_fd;

            /* What IO events did happen? */
            mpd_async_event io_eventmask;

            /* The actual events (like "player","mixer".. etc) */
            unsigned idle_events;

            /* A functor representing the io_callback */
            sigc::connection io_functor;

            /* emit() is called on this on events */
            EventNotifier * mp_Notifier;

            /* MPD Status */
            Status * mp_Status;

            /* Synchronous connection */
            Connection * mp_Conn;

            /* The data passed to the observer */
            NotifyData m_NData;
    };
}
#endif
