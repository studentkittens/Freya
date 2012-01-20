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
#include "Writer.hh"
#include "../Init/Path.hh"

#include <stdlib.h>
#include <string.h>
#include <time.h>

/* for: g_strdup_printf() */
#include <glib.h>

/* for: g_vasprintf() */
#include <glib/gprintf.h>

#define TIME_BUF_SIZE 128

/* Clear after 2MB logsize */
#define MAX_LOG_SIZE (2 * 1024 * 1024)

/* Those colors work sadly only on Unix
 * win32 will just print out the actual escapes,
 * (users of powershell might see color though)
 * */
#define COL_RED "\x1b[31;01m"
#define COL_YEL "\x1b[33;01m"
#define COL_GRE "\x1b[32;01m"
#define COL_BLU "\x1b[34;01m"
#define COL_NCO "\x1b[0m"

namespace Log
{
    /*-----------------------------------------------*/

    Writer::Writer() : m_Verbosity(LOG_DEBUG)
    {
        Init::Path path_getter;
        m_Logpath = path_getter.path_to_log();

        m_Logfile = fopen(m_Logpath.c_str(),"a");
        if(m_Logfile != NULL)
        {
            GStatBuf buf;
            g_stat(m_Logpath.c_str(),&buf);
            if(buf.st_size >= MAX_LOG_SIZE)
            {
                g_message("Clearing Log because it's size exceeds %d Bytes.",MAX_LOG_SIZE);
                clear();
            }

            fprintf(m_Logfile,"#####################################\n");
        }
        else
        {
            perror("Cannot write to logfile");
            g_error("Tried to write it at: %s",m_Logpath.c_str());
        }
    }

    /*-----------------------------------------------*/

    Writer::~Writer()
    {
        if(this->m_Logfile != NULL)
        {
            fclose(m_Logfile);
        }
    }

    /*-----------------------------------------------*/

    void Writer::message(const char * File, int Line, LOGLEVEL level, const char * fmt, ...)
    {
        if(this->m_Logfile != NULL && level <= m_Verbosity)
        {
            /* Write all va_args in the tmp_buf,
             * allocate memory as necessary */
            gchar * tmp_buf = NULL;
            va_list params;
            va_start(params,fmt);
            g_vasprintf(&tmp_buf,fmt,params);
            va_end(params);

            /* Write current time in the buffer */
            char buffer[TIME_BUF_SIZE] = {0};
            get_current_time(buffer);

            /* Convert enum to an approp. string */
            bool append_location = false;
            const char * title = convert_enum_to_str(level,append_location);

            std::stringstream bufstream;

            /* Add Prefix */
            bufstream << "[" << title << " " << buffer << "] ";

            /* Infix the message */
            bufstream << tmp_buf;

            /* Do the suffix */
            if(append_location)
                bufstream << " (" << Glib::path_get_basename(File) << ":" << Line << ")";

            bufstream << std::endl;

            /* Write it to all streams */
            std::string format = bufstream.str();
            fwrite(format.c_str(),1,format.size(),m_Logfile);
            fwrite(format.c_str(),1,format.size(),stderr);
            fflush(m_Logfile);

            /* Format is dyn. allocated - free */
            g_free(tmp_buf);
        }
    }

    /*-----------------------------------------------*/

    const char* Writer::convert_enum_to_str(LOGLEVEL level, bool& append_location)
    {
        switch(level)
        {
        case LOG_OK:
            append_location = false;
            return COL_GRE"DONE "COL_NCO;
        case LOG_ERROR:
            append_location = true;
            return COL_RED"ERROR"COL_NCO;
        case LOG_FATAL_ERROR:
            append_location = true;
            return COL_RED"FATAL"COL_NCO;
        case LOG_INFO:
            append_location = false;
            return COL_NCO"INFO "COL_NCO;
        case LOG_WARN:
            append_location = true;
            return COL_YEL"WARN "COL_NCO;
        case LOG_DEBUG:
            append_location = true;
            return COL_BLU"DEBUG"COL_NCO;
        default:
            append_location = false;
            return COL_NCO"INFO "COL_NCO;
        }
    }

    /*-----------------------------------------------*/
    
    void Writer::set_verbosity(LOGLEVEL v)
    {
        m_Verbosity = CLAMP(v,(LOGLEVEL)0,LOG_DEBUG);
    }
    
    /*-----------------------------------------------*/
    
    LOGLEVEL Writer::get_verbosity()
    {
        return m_Verbosity;
    }
    
    /*-----------------------------------------------*/

    void Writer::clear()
    {
        if(m_Logfile != NULL)
        {
            fclose(m_Logfile);
            m_Logfile = fopen(m_Logpath.c_str(),"w");
        }
    }

    /*-----------------------------------------------*/

    void Writer::get_current_time(char buffer[])
    {
        struct tm * timeinfo = NULL;
        time_t rawtime = time(NULL);
        timeinfo = localtime(&rawtime);
        strftime(buffer, TIME_BUF_SIZE,"%H:%M:%S", timeinfo);
    }
}
