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
#ifndef FREYA_BASECLIENT_GUARD
#define FREYA_BASECLIENT_GUARD

#include "Listener.hh"
#include "Connection.hh"

namespace MPD
{

    /**
     * @brief You can call connect on this.
     *
     * It gets emitted by the client whenever the connection changes,
     * i.e. when getting disconnected or connected, in former case 
     * 'false' is passed as argument, in the latter 'true'
     */
    typedef sigc::signal<void,bool> ConnectionNotifier;
    
    /**
     * @brief The Base to MPD::Client
     *
     * BaseClient does not offer any special command it can send to the server,
     * but is able to set up everything related to connections, i.e setting up
     * the Listener and the connection or reconnection once connection is lost
     * connect() is not a public method, since you are not supposed to instanciate 
     * this class, MPD::Client offers the connect() you want to use.
     *
     * The splitting between BaseClient and Client was done to allow Client Extensions,
     * i.e. AudioOutput, that implements certain mpd commands to enable audio outputs.
     */
    class BaseClient
    {
        public:
            /**
             * @brief Go into idle mode, you are not allowed to send commands while idling!
             */
            void go_idle(void);
            /**
             * @brief Leave idle mode, so you can send commands to the server
             */
            void go_busy(void);

            /**
             * @brief Returns the underlying connection
             *
             * You are not supposed to call this as user of the client,
             * it's use is intended as client extension that need to 
             * send it's own commands to MPD.
             *
             * @return A ref to a MPD::Connection
             */
            Connection& get_connection(void);
    
            /**
             * @brief true if connected
             *
             * @return 
             */
            bool is_connected(void);

            /**
             * @brief Start a commandlist
             */
            void begin(void);
            /**
             * @brief Commit the commandlist
             */
            void commit(void);
            
            /**
             * @brief Get the current MPD::Status
             *
             * @return A reference to it. Do not modify.
             */
            Status * get_status(void);
            
            /**
             * @brief Get the notify sigc::signal
             *
             * Use connect() on it. This is called always once a ne, ...w event
             * happens. See the typedef in Listener.hh for the exact signature
             *
             * @return the sigc::signal
             */
            EventNotifier& signal_client_update(void);

            /**
             * @brief Register for connection changes
             *
             * @return a sigc::signal, you can call connect() on
             */
            ConnectionNotifier& signal_connection_change(void);

            /**
             * @brief Forces client update
             *
             * Updates status, stats, current song 
             * and sends all possible events to all connected listeners
             *
             */
            void force_update(void);

        protected:
            
            /**
             * @brief Do not allow to instantiate BaseClient
             */
            BaseClient(void);
           
            /**
             * @brief This is called internally by MPD::Client and does the actual connect work
             *
             * @return is_connected()
             */
            bool __connect(void);
            /**
             * @brief Same as __connect()
             *
             * @return is_connected()
             */
            bool __disconnect(void);

            /**
             * @brief Called periodically when mpd disconnects us
             *
             * This usually happens when mpd server was killed.
             * Then this function tries to reconnect you
             *
             * @return It returns false once reconnected (which means: Remove mainloopsource)
             */
            gboolean timeout_reconnect(void);

            /**
             * @brief Called when MPD::Connection notices an connection error
             *
             * @param is_fatal the error is fatal 
             * @param err the error code
             */
            void handle_errors(bool is_fatal, mpd_error err);

            /**
             * @brief The connection to the MPD server
             */
            MPD::Connection m_Conn;
            /**
             * @brief Event Listener
             */
            MPD::Listener * mp_Listener;
            
            /**
             * @brief BaseClient::begin() was called but not yet BaseClient::commit()
             */
            bool m_ListBegun;
            
            /**
             * @brief Listener calls emit() on this once events happen.
             */
            EventNotifier m_Notifier;

            /**
             * @brief Connection Errors are reported through this.
             */
            ConnectionNotifier m_ConnNotifer;
    };
}

#endif /* end of include guard: FREYA_BASECLIENT_GUARD */
