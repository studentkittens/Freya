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
/*  Sample test */
#include <cxxtest/TestSuite.h>
#include "Writer.hh"
#include "../Init/Path.hh"
#include <cstring>
#include <glib.h>
#include <glib/gstdio.h>


/* The whole suite. One suit for each module. */
class LogTestSuite : public CxxTest::TestSuite
{
public:
    /* some blackbox testing of log::writer */
    void testLogWriter( void )
    {
        Init::Path path;
        int aval = 0;
        long fsize_a,fsize_b = 0;
        GStatBuf statbuf;
        memset(&statbuf,0,sizeof(GStatBuf));

        /* gets a logwriter instance, should create a log if not avaiable */
        Log::Writer::instance();
        aval = g_stat(path.path_to_log().c_str(),&statbuf);

        if(aval != -1)
        {
            fsize_a = statbuf.st_size;
            printf("filesize var_a: %ld bytes. \n",fsize_a);

            fsize_b = statbuf.st_size;
            printf("filesize var_b: %ld bytes. \n",fsize_b);

            /* log size equal? */
            TS_ASSERT_EQUALS(fsize_a,fsize_b);

            /* writing a message to log, messeage should grow by 12 bytes + 64 bytes date/log footprint */
            Info("test message");
            printf("writing message to log.\n");

            /*reinit stat struct and get new filesize */
            g_stat(path.path_to_log().c_str(),&statbuf);
            fsize_b = statbuf.st_size;
            printf("new filesize var_b: %ld bytes. \n",fsize_b);

            /* file_b bigger after writing to log? */
            TS_ASSERT(fsize_a < fsize_b);

            /* file_b size increased properly? file_a + written bytes? */
            TS_ASSERT(fsize_a+12+64 == fsize_b);
        }
        else
        {
            TS_FAIL("error occured, logfile possibly not avaiable.");
        }
    }

};
