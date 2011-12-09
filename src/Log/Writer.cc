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

/* Those work sadly only on Unix 
 * win32 will just print out the actual escapes
 * */
#define COL_RED "\x1b[31;01m"
#define COL_YEL "\x1b[33;01m"
#define COL_GRE "\x1b[32;01m"
#define COL_BLU "\x1b[34;01m"
#define COL_NCO "\x1b[0m"

namespace Log
{
    /*-----------------------------------------------*/

    // constructor
    Writer::Writer()
    {
        Init::Path path_getter;        
        m_Logpath = path_getter.path_to_log();

        m_Logfile = fopen(m_Logpath.c_str(),"a");
        if(m_Logfile != NULL)
        {
            fprintf(m_Logfile,"#####################################\n");
        }
        else
        {
            perror("Cannot write to logfile");
            g_error("Tried to write it at: %s",m_Logpath.c_str());
        }
    }

    /*-----------------------------------------------*/

    // destructor
    Writer::~Writer()
    {
        if(this->m_Logfile != NULL) {
            fclose(m_Logfile);
        }
    }

    /*-----------------------------------------------*/

    // message method to print a message into the logfile with LOGLEVEL
    void Writer::message(const char * File, int Line, LOGLEVEL level, const char * fmt, ...) 
    {
        if(this->m_Logfile != NULL)
        {
            gchar * tmp_buf = NULL;

            va_list params;
            va_start(params,fmt);
            g_vasprintf(&tmp_buf,fmt,params);
            va_end(params);

            char buffer[TIME_BUF_SIZE] = {0};
            get_current_time(buffer);

            /* Formatting */
            gchar * format = g_strdup_printf("[%s - %s] %s (at %s:%d)\n", convert_enum_to_str(level), buffer, tmp_buf, File, Line);
            gsize fmt_len = strlen(format);

            /* Write it to all streams */
            fwrite(format,1,fmt_len,m_Logfile);
            fwrite(format,1,fmt_len,stderr);
            fflush(m_Logfile);

            /* Format is dyn. allocated - free */
            g_free(format);
            g_free(tmp_buf);
        }
    }

    /*-----------------------------------------------*/

    const char* Writer::convert_enum_to_str(LOGLEVEL level) 
    {
        switch(level) {
            case LOG_OK: 
                return COL_GRE"DONE "COL_NCO;
            case LOG_ERROR:
                return COL_RED"ERROR"COL_NCO;
            case LOG_FATAL_ERROR:
                return COL_RED"FATAL"COL_NCO;
            case LOG_INFO:
                return COL_NCO"INFO "COL_NCO;
            case LOG_WARN:
                return COL_YEL"WARN "COL_NCO;
            case LOG_DEBUG: 
                return COL_BLU"DEBUG"COL_NCO;
            default:
                return COL_NCO"INFO "COL_NCO;
        }
    }

    /*-----------------------------------------------*/

    void Writer::clear(void)
    {
        if(this->m_Logfile != NULL)
        {
            fclose(m_Logfile);
            this->m_Logfile = fopen(m_Logpath.c_str(),"w");
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
