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

public:

    /* Fixtures */
    void setUp(void) {
       LogSetVerbosity(Log::LOG_WARN);
       clientUpdated = false;
       connectionChanged = false;
       cl.signal_client_update().connect(sigc::mem_fun(*this,&MPDTestSuite::clientUpdate));
       cl.signal_connection_change().connect(sigc::mem_fun(*this,&MPDTestSuite::connectionChange));
       cl.connect();
    }

    void tearDown(void) {
        cl.disconnect();
        connectionChanged = false;
        clientUpdated = false;
    }

    void connectionChange(bool server_changed, bool is_connected)
    {
        connectionChanged = is_connected;
    }
    
    void clientUpdate(enum mpd_idle, MPD::NotifyData& data)
    {
        clientUpdated = true;
    }

    /* --- */

    void testConnect(void)
    {
        TS_ASSERT(connectionChanged);
        TS_ASSERT(cl.ping());
        TS_ASSERT(cl.is_connected());
    }

    void testDisconnect(void)
    {
        cl.disconnect();
        TS_ASSERT(!connectionChanged);
        TS_ASSERT(!cl.ping());
        TS_ASSERT(!cl.is_connected());
        cl.connect();
        testConnect();
    }

    void testSignalClientUpdate(void)
    {
        // connect() should call force_update()
        TS_ASSERT(clientUpdated);
        clientUpdated = false;
        // lets call it ourselves
        cl.force_update();
        TS_ASSERT(clientUpdated);
        clientUpdated = false;
    }
};
