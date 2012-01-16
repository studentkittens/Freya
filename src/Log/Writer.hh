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
#ifndef FREYA_LOG_WRITER_GUARD
#define FREYA_LOG_WRITER_GUARD

#include <glibmm.h>
#include <stdio.h>
#include "../Utils/Singleton.hh"

/* Not supposed to used directly, use the macros below */
#define _MSG(level, msg, ...) Log::Writer::instance().message(__FILE__, __LINE__, level, msg,  ##__VA_ARGS__)
#define LogSetVerbosity(X) Log::Writer::instance().set_verbosity((Log::LOGLEVEL)X)
#define LogGetVerbosity Log::Writer::instance().get_verbosity()

/* The actual macros */
#define Warning(msg, ...)  _MSG(Log::LOG_WARN, msg, ##__VA_ARGS__)
#define Info(msg, ...)     _MSG(Log::LOG_INFO, msg, ##__VA_ARGS__)
#define Fatal(msg, ...)    _MSG(Log::LOG_FATAL_ERROR, msg, ##__VA_ARGS__)
#define Error(msg, ...)    _MSG(Log::LOG_ERROR, msg, ##__VA_ARGS__)
#define Debug(msg, ...)    _MSG(Log::LOG_DEBUG, msg, ##__VA_ARGS__)
#define Success(msg, ...)  _MSG(Log::LOG_OK, msg, ##__VA_ARGS__)

namespace Log
{
    /**
     * @brief Log severity, influencing the color.
     */
    enum LOGLEVEL
    {
        LOG_FATAL_ERROR = 1,
        LOG_ERROR,
        LOG_WARN,
        LOG_OK,
        LOG_INFO,
        LOG_DEBUG
    };

    class Writer
    {
        /* Make this class a singleton,
         * this implicitely defines a ctor,
         * Just the dtor is defined expl. below.
         */
        DEF_SINGLETON(Writer);

    public:

        /**
         * @brief Closes the Log also properly. It is not fatal when not being called.
         */
        ~Writer();

        /**
         * @brief Actual instance method called. Do not use directly!
         *
         * @param file Passed by the macro.
         * @param line Passed by the macro.
         * @param level Severitylevel
         * @param msg Actual message
         * @param ... a va_list to allow printf style logging
         */
        void message(const char *file, int line, LOGLEVEL level, const char *msg, ...);

        /**
         * @brief Set the max. verbosity
         *
         * LOG_DEBUG is the highest level, LOG_FATAL_ERROR the lowest,
         * the priority can be read from the LOGLEVEL enum above,
         * to diasable logging completely you may pass 0.
         * 
         * @param v a member of the LOGLEVEL enum
         */
        void set_verbosity(LOGLEVEL v);

        /**
         * @brief Get the currently set verbosity level
         *
         * @return a member of the LOGLEVEL enum
         */
        LOGLEVEL get_verbosity();

        /**
         * @brief Clear the logfile (but keep it open)
         */
        void clear(void);

    private:

        /**
         * @brief Path to logfile
         */
        Glib::ustring m_Logpath;
        /**
         * @brief Filehandle
         */
        FILE * m_Logfile;

        /**
         * @brief Max. verbosity
         */
        LOGLEVEL m_Verbosity; 

        /**
         * @brief Translate LOGLEVEL to a string
         *
         * @return Converted string as const char *
         */
        const char * convert_enum_to_str(LOGLEVEL level, bool& append_location);
        /**
         * @brief get current time as timestamp
         *
         * @param buffer[] output argument, must be at least 20 bytes in size
         */
        void get_current_time(char buffer[]);
    };
}

#endif
