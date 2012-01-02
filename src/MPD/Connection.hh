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
#ifndef FREYA_MPDCONNECTION_GUARD
#define FREYA_MPDCONNECTION_GUARD

#include <mpd/client.h>
#include <glibmm.h>

namespace MPD
{
    /**
     * @brief You can call sigc::signal::connect() on this.
     *
     * It gets emitted by the client whenever the connection changes,
     * i.e. when getting disconnected or connected, in former case
     * 'false' is passed as argument, in the latter 'true'
     */
    typedef sigc::signal<void,bool,bool> ConnectionNotifier;

    /**
     * @brief Called once check_error() notices an error.
     */
    typedef sigc::signal<void, bool,mpd_error> ErrorNotify;

    /**
     * @brief A convinience Wrapper around mpd_connection*
     *
     * It features error notifying, error clearing,
     * and doing the actual connection work.
     */
    class Connection
    {
    public:

        /**
         * @brief Initializes a new connection object
         */
        Connection(void);
        /**
         * @brief Automatically disconnects
         */
        ~Connection(void);

        /**
         * @brief is connected?
         *
         * @return true if connected
         */
        bool is_connected(void);

        /**
         * @brief Tries to connect accordingly to the values in the config
         *
         * is_connected() hast to be false.
         *
         * @return true on success
         */
        bool connect(void);
        /**
         * @brief Disconnects connection
         *
         * @return true on success
         */
        bool disconnect(void);
        /**
         * @brief Clears any occured errors
         *
         * If an error occured you might have to call this before
         * you continue to use the connection, mostly this called
         * automatically by check_error(), which is executed in
         * every idle/busy cycle.
         *
         * @return true if error was not fatal
         */
        bool clear_error(void);

        /**
         * @brief check if an error occured
         *
         * Clears error, calls emit() on ErrorNotify
         *
         * @return true if yes
         */
        bool check_error(void);

        /**
         * @brief get a sigc::connection that is emit()'d once an error occures
         *
         * @return a ref to a sigc::signal - call connect() on it
         */
        ErrorNotify& signal_error(void);

        /**
         * @brief Use this to register for connection changes
         *
         * @return a ref to a sigc::signal - call connect() on it
         */
        ConnectionNotifier& signal_connection_change(void);

        /**
         * @brief Call emit() on the ConnectionNotifier signal
         *
         * This is a separate function because one want to emit the signal
         * after making other things ready first.
         * You have to call connect() or disconnect() BEFORE emitting though!
         */
        void emit_connection_change(void);

        /**
         * @brief Returns the underlying C structure
         *
         * @return NULL if disconnected.
         */
        mpd_connection * get_connection(void);


    private:

        /**
         * @brief Connects / Disconnects  are reported through this.
         */
        ConnectionNotifier m_ConnNotifer;

        /**
         * @brief The connection from libmpdclient to MPD
         */
        mpd_connection * conn;

        /**
         * @brief Emit is called on this when check_error() reports an error
         */
        ErrorNotify m_ErrorSig;

        /**
         * @brief Current host connected to
         */
        Glib::ustring lastHost;
        /**
         * @brief True if host changed between two connects
         */
        bool hostChanged;
    };

}

#endif
