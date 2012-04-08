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
#include <stdio.h>
#include <time.h>
#include <glib.h>

#include "Utils.hh"
#include "CompileSymbols.hh"

#include <giomm/memoryinputstream.h>

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
    char durstr[BUFFER] = {0 };
    if(week != 0)
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
    strftime(retv,512, "%F",timestr);
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

/*-----------------------*/

void builder_internal_fetch(Glib::RefPtr<Gtk::Builder>& ref, const char * file)
{
    const char * defs = CompileSymbols::instance().get_defs(file);
    try
    {
        if(defs == NULL)
        {
            Debug("Fetching from file: %s",file);
            ref->add_from_file(file);
        }
        else
        {
            Debug("Fetching from Memory: %s",file);
            ref->add_from_string(defs,-1);
        }
    }
    catch(const Gtk::BuilderError& e)
    {
        Error("Unable to load .glade file:\n"
              "    Reason:  %s            \n"
              "    Is '%s' a valid path?  \n",
              e.what().c_str(),file);
    }
}

/*-----------------------*/

Glib::RefPtr<Gdk::Pixbuf> create_pixbuf_from_data(const guchar * data, gsize len, int width, int height, bool aspect)
{
    Glib::RefPtr<Gio::MemoryInputStream> is = Gio::MemoryInputStream::create();
    if(is)
    {
        is->add_data(data,len);
    }
    if(width == -1 && height == -1)
    {
        return Gdk::Pixbuf::create_from_stream(is);
    }
    else
    {
        return Gdk::Pixbuf::create_from_stream_at_scale(is,width,height,aspect);
    }
}

/*-----------------------*/

Glib::RefPtr<Gdk::Pixbuf> pixbuf_internal_fetch(const char * file, int width, int height, bool aspect)
{
    const char * defs = CompileSymbols::instance().get_defs(file);
    if(defs == NULL)
    {
        Debug("Fetching image from FS: %s",file);
        std::string sfile(file);
        if(width == -1 && height == -1)
        {
            return Gdk::Pixbuf::create_from_file(sfile);
        }
        else
        {
            return Gdk::Pixbuf::create_from_file(sfile,width,height,aspect);
        }
    }
    else
    {
        Debug("Fetching image from memory: %s",file);
        gsize out_len = 0;
        guchar * imgdata = g_base64_decode(defs,&out_len);
        return create_pixbuf_from_data(imgdata,out_len,width,height,aspect);
    }
}
}
