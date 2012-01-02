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
#include <stdio.h>
#include <time.h>
#include <glib.h>

#include "Utils.hh"

namespace Utils
{

    Glib::ustring seconds_to_duration(unsigned long duration)
    {
        const int BUFFER = 512;
        const int WEEK_IN_SEC = 604800;
        const int DAY_IN_SEC = 86400;
        const int HOUR_IN_SEC = 3600;
        const int MIN_IN_SEC = 60;


        int week = duration/WEEK_IN_SEC;
        duration %= WEEK_IN_SEC;

        int day = duration/DAY_IN_SEC;
        duration %= DAY_IN_SEC;

        int hour = duration/HOUR_IN_SEC;
        duration %= HOUR_IN_SEC;

        int min = duration/MIN_IN_SEC;
        duration %= MIN_IN_SEC;

        int sec = duration;

        char durstr[BUFFER] = {0};

        if (week != 0)
        {
            g_snprintf(durstr,BUFFER,"%d weeks %d days %d hours %d minutes %d seconds",week,day,hour,min,sec);
        }
        else if(day != 0)
        {

            g_snprintf(durstr,BUFFER,"%d days %d hours %d minutes %d seconds",day,hour,min,sec);
        }
        else
        {

            g_snprintf(durstr,BUFFER,"%d hours %d minutes %d seconds",hour,min,sec);
        }
        Glib::ustring retv = durstr;

        return retv;
    }

    /*-----------------------*/

    Glib::ustring seconds_to_timestamp(const long duration)
    {
        int const BUFFER = 512;

        struct tm *timestr = NULL;
        timestr = localtime(&duration);

        char retv[BUFFER];
        strftime (retv,512, "%F",timestr);

        return Glib::ustring(retv);
    }

    /*-----------------------*/

    std::string int_to_string(int num)
    {
        unsigned size = (ABS(num) % 10) + 2;
        char num_buf[size];
        g_snprintf(num_buf,size,"%d",num);
        return std::string(num_buf);
    }
}
