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
#ifndef FREYA_BASECLIENT_GUARD
#define FREYA_BASECLIENT_GUARD

#include "Listener.hh"
#include "Connection.hh"
#include "Query.hh"

namespace MPD
{
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
    void go_idle();
    /**
     * @brief Leave idle mode, so you can send commands to the server
     */
    void go_busy();

    /**
     * @brief Returns the underlying connection
     *
     * You are not supposed to call this as user of the client,
     * it's use is intended as client extension that need to
     * send it's own commands to MPD.
     *
     * @return A ref to a MPD::Connection
     */
    Connection& get_connection();

    /**
     * @brief true if connected
     *
     * @return
     */
    bool is_connected();

    /**
     * @brief Start a commandlist
     */
    void begin();
    /**
     * @brief Commit the commandlist
     */
    void commit();

    /**
     * @brief Get the current MPD::Status
     *
     * WARNING: This function does not guarantee to be up-to-date!!!
     * If you need always the last status you may have to register for
     * client updates, since the mainloop iteration might take a few cycles.
     * It is therefore not encouraged to be used.
     *
     * @return A reference to it. Do not modify.
     */
    Status * get_status();

    /**
     * @brief Get the notify sigc::signal
     *
     * Use connect() on it. This is called always once a new event
     * happens. See the typedef in Listener.hh for the exact signature
     *
     * @return the sigc::signal
     */
    EventNotifier& signal_client_update();

    /**
     * @brief Register for connection changes
     *
     * @return a sigc::signal, you can call connect() on
     */
    ConnectionNotifier& signal_connection_change();

    /**
     * @brief Forces client update
     *
     * Updates status, stats, current song
     * and sends all possible events to all connected listeners
     *
     */
    void force_update();

    /**
     * @brief Creates a Query to search songs in the the Database
     *
     * @param exact Exact or fuzzy matching?
     *
     * @return A newly allocated Query, delete after use
     */
    Query * create_db_songs_query(bool exact = false);

    /**
     * @brief Creates a Query to search tags in the Database
     *
     * @param tag
     *
     * @return
     */
    Query * create_db_tag_query(mpd_tag_type tag);

protected:

    /**
     * @brief Do not allow to instantiate BaseClient
     */
    BaseClient();

    virtual ~BaseClient() {}

    /**
     * @brief This is called internally by MPD::Client and does the actual connect work
     *
     * @return is_connected()
     */
    bool __connect();
    /**
     * @brief Same as __connect()
     *
     * @return is_connected()
     */
    bool __disconnect();

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

private:

    /**
     * @brief Called periodically when mpd disconnects us
     *
     * This usually happens when mpd server was killed.
     * Then this function tries to reconnect you
     *
     * @return It returns false once reconnected (which means: Remove mainloopsource)
     */
    gboolean timeout_reconnect();

    /**
     * @brief Called when MPD::Connection notices an connection error
     *
     * @param is_fatal the error is fatal
     * @param err the error code
     */
    void handle_errors(bool is_fatal, mpd_error err);

    /**
     * @brief Listener calls emit() on this once events happen.
     */
    EventNotifier m_Notifier;
};
}

#endif /* end of include guard: FREYA_BASECLIENT_GUARD */
