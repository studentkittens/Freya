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
#include <cxxtest/TestSuite.h>
#include "Client.hh"
#include <glib.h>
#include <glib/gstdio.h>
#include "../Log/Writer.hh"

/* The whole suite. One suit for each module. */
class MPDTestSuite : public CxxTest::TestSuite
{
    MPD::Client cl;
    bool clientUpdated;
    bool connectionChanged;
    bool isFirstRun; 
    
public:

    /* Fixtures */
    void setUp() {
       LogSetVerbosity(Log::LOG_WARN);
       clientUpdated = false;
       connectionChanged = false;
       isFirstRun = true;

       /* Connect signals */
       cl.signal_client_update().connect(
               sigc::mem_fun(*this,&MPDTestSuite::clientUpdate));
       cl.signal_connection_change().connect(
               sigc::mem_fun(*this,&MPDTestSuite::connectionChange));

       cl.connect();
    }

    void tearDown() {
        cl.disconnect();
        connectionChanged = false;
        clientUpdated = false;
    }

    /* -- Signals -- */

    void connectionChange(bool server_changed, bool is_connected)
    {
        connectionChanged = is_connected;
    }
    
    void clientUpdate(enum mpd_idle, MPD::NotifyData& data)
    {
        clientUpdated = true;
    }

    /* --- */

    void testConnect()
    {
        // All those should indicate we're connected
        TS_ASSERT(connectionChanged);
        TS_ASSERT(cl.ping());
        TS_ASSERT(cl.is_connected());
    }

    void testDisconnect()
    {
        cl.disconnect();
        TS_ASSERT(!connectionChanged);
        TS_ASSERT(!cl.ping());
        TS_ASSERT(!cl.is_connected());
        cl.connect();
        testConnect();
    }

    void testSignalClientUpdate()
    {
        // connect() should call force_update()
        TS_ASSERT(clientUpdated);
        clientUpdated = false;
        // lets call it ourselves
        cl.force_update();
        TS_ASSERT(clientUpdated);
        clientUpdated = false;
    }

    bool toggleStates[4];
    
    /* Exemplary test of one client command */
    void toggleCommandsClientUpdate(mpd_idle event, MPD::NotifyData& data) {
        TS_ASSERT(data.get_status().get_random() == toggleStates[0]);
        TS_ASSERT(data.get_status().get_consume() == toggleStates[1]);
        TS_ASSERT(data.get_status().get_single() == toggleStates[2]);
        TS_ASSERT(data.get_status().get_repeat() == toggleStates[3]);
    }

    void testToggleCommands() {
        toggleStates[0] = cl.get_status()->get_random();
        toggleStates[1] = cl.get_status()->get_consume();
        toggleStates[2] = cl.get_status()->get_single();
        toggleStates[3] = cl.get_status()->get_repeat();

        cl.toggle_random();
        cl.toggle_consume();
        cl.toggle_single();
        cl.toggle_repeat();

        if(isFirstRun)
        {
            isFirstRun = false;
            testToggleCommands();
        }
    }
};
