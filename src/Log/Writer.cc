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

/* for: time() */
#include <time.h>

/* for: g_strdup_printf() */
#include <glib/gstdio.h>

/* for: g_vasprintf() */
#include <glib/gprintf.h>

/* for: Glib::get_basename() */
#include <glibmm/miscutils.h>

#define TIME_BUF_SIZE 128

/* Clear after 2MB logsize */
#define MAX_LOG_SIZE (2 * 1024 * 1024)

namespace Log {
    /* Termcolors 
     * Based on: http://linuxgazette.net/issue65/padala.html
     */ 
    typedef enum {
        RESET,
        BRIGHT,
        DIM,
        UNDERLINE,
        BLINK,
        REVERSE,
        HIDDEN		
    } termattribute;
    
    /////////////////////////////

    typedef enum {
        BLACK,
        RED,
        GREEN,
        YELLOW,
        BLUE,
        MAGENTA,
        CYAN,
        WHITE 
    } termcolor;

    /////////////////////////////

    struct LogDetail
    {
        termattribute attr;
        termcolor color;
        const char * text;
        bool detail;
        bool usedomain; 
    };

    /////////////////////////////


    LogDetail __info[] = {
        {RESET, BLACK,   "None",     false, false },
        {RESET, MAGENTA, "Critical", true,  true  },
        {RESET, RED,     "Error  ",  true,  true  },
        {RESET, YELLOW,  "Warning",  true,  true  },
        {RESET, GREEN,   "Done   ",  false, false },
        {RESET, WHITE,   "Info   ",  false, false },
        {RESET, BLUE,    "Debug  ",  true,  true  }
    };

    /////////////////////////////
    
    static void resetcolor(FILE * stream)
    {
        fprintf(stream,"%c[0m",0x1B);
    }
    
    /////////////////////////////

    static void textcolor(FILE * stream, termattribute attr, termcolor fg)
    {	
        /* 
         * Command is the control command to the terminal 
         */
        fprintf(stream,"%c[%d;%dm", 0x1B, attr, fg + 30);
    }

    /////////////////////////////
    
    static void glib_logging(const gchar *log_domain,GLogLevelFlags log_level,const gchar *message, gpointer user_data)
    {        
        switch(log_level) {
            case G_LOG_LEVEL_CRITICAL:
                Critical(message);
                break;
            case G_LOG_LEVEL_ERROR:
                Error(message);
                break;
            case G_LOG_LEVEL_WARNING:      
                Warning(message);
                break;
            case G_LOG_LEVEL_MESSAGE:         
                Success(message);
                break;
            case G_LOG_LEVEL_INFO:         
                Info(message);
                break;
            case G_LOG_LEVEL_DEBUG:
                Debug(message);
               break; 
            case G_LOG_FLAG_RECURSION:
            case G_LOG_FLAG_FATAL:
            case G_LOG_LEVEL_MASK:
            default:
               break;
        }
    }

    /////////////////////////////
    
    static void register_log_domains(const char * domain)
    {
        g_log_set_handler(domain,
               (GLogLevelFlags)(G_LOG_LEVEL_MASK | G_LOG_FLAG_FATAL| G_LOG_FLAG_RECURSION),
               glib_logging, NULL);
    }
    
    /////////////////////////////

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

            fprintf(m_Logfile,"\n---- cut here ----\n\n");
        }
        else
        {
            perror("Cannot write to logfile");
            g_error("Tried to write it at: %s",m_Logpath.c_str());
        }

        register_log_domains("Glib");
        register_log_domains("Glib-GObject");
        register_log_domains("Gtk");
    }

    /////////////////////////////

    Writer::~Writer()
    {
        if(m_Logfile != NULL)
        {
            fclose(m_Logfile);
        }
    }

    /////////////////////////////

    void Writer::write_out(std::stringstream& stream)
    {
        std::string format = stream.str();
        fwrite(format.c_str(),1,format.size(),m_Logfile);
        fwrite(format.c_str(),1,format.size(),stderr);
        fflush(m_Logfile);
    }
    
    /////////////////////////////
    
    std::string get_domain_from_file(const char * file_path)
    {
        std::string dir = Glib::path_get_dirname(file_path);
        return dir.substr(dir.find_last_of(G_DIR_SEPARATOR) + 1);
    }
    
    /////////////////////////////

#define PRINT_LOG_PART(expression) \
    {                              \
        std::stringstream buf;     \
        buf << expression ;        \
        write_out(buf);            \
    }                              \


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

            LogDetail &logInfo = __info[level];
            {
                textcolor(stderr,logInfo.attr,logInfo.color);
                PRINT_LOG_PART("[" << logInfo.text << " " << buffer << "]");
                resetcolor(stderr);

                if(logInfo.usedomain)
                {
                    textcolor(stderr,logInfo.attr,MAGENTA);
                    PRINT_LOG_PART("[" << get_domain_from_file(File) << "]");
                    resetcolor(stderr);
                }

                PRINT_LOG_PART(" " << tmp_buf);

                if(logInfo.detail) 
                {
                    textcolor(stderr,logInfo.attr,logInfo.color);
                    PRINT_LOG_PART(" (" << Glib::path_get_basename(File) << ":" << Line << ")");
                    resetcolor(stderr);
                }

                PRINT_LOG_PART(std::endl);
            }

            /* Format is dyn. allocated - free */
            g_free(tmp_buf);
        }
    }

    /////////////////////////////

    void Writer::set_verbosity(LOGLEVEL v)
    {
        m_Verbosity = CLAMP(v,(LOGLEVEL)0,LOG_NUMS_OF_LEVEL);
    }

    /////////////////////////////

    LOGLEVEL Writer::get_verbosity()
    {
        return m_Verbosity;
    }

    /////////////////////////////

    void Writer::clear()
    {
        if(m_Logfile != NULL)
        {
            fclose(m_Logfile);
            m_Logfile = fopen(m_Logpath.c_str(),"w");
        }
    }

    /////////////////////////////

    void Writer::get_current_time(char buffer[])
    {
        struct tm * timeinfo = NULL;
        time_t rawtime = time(NULL);
        timeinfo = localtime(&rawtime);
        strftime(buffer, TIME_BUF_SIZE,"%H:%M:%S", timeinfo);
    }
}
