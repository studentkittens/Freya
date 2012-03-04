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
#ifndef FREYA_CONFIG_HANDLER_89V106EN
#define FREYA_CONFIG_HANDLER_89V106EN

#include <libxml/parser.h>
#include <glibmm/ustring.h>

#include "Model.hh"
#include "../Utils/Singleton.hh"

namespace Config
{
    /**
     * @brief A singleton class to provide Config access, use the macros down instead
     */
    class Handler
    {
        DEF_SINGLETON( Handler )

    public:
        ~Handler ();

        /**
         * @brief value getter for config option, use CONFIG_GET(x) macro instead
         *
         * @param Glib::ustring, config option url as ustring, e.g. settings.connection.host
         *
         * @return value as ustring if exists, if not, empty ustring is returned
         */
        Glib::ustring get_value(Glib::ustring);

        /**
         * @brief int value getter for config option, use CONFIG_GET_AS_INT(x) macro instead
         *
         * @param Glib::ustring, config option url as ustring, e.g. settings.connection.autoconnect
         *
         * @return int value if exists, if not, -1 is returned
         */
        int get_value_as_int(Glib::ustring);

        /**
         * @brief value setter for config option, use CONFIG_SET(x,y) macro instead
         *
         * @param Glib::ustring, config option url as ustring, e.g. settings.connection.host
         * @param Glib::ustring, option value to be set, e.g. localhost
         */
        void set_value(Glib::ustring, Glib::ustring);


        /**
         * @brief int value setter for config option, use CONFIG_SET_AS_INT(x,y) macro instead
         *
         * @param Glib::ustring,config option url as ustring, e.g. settings.connection.port
         * @param int, option value to be set, e.g. 6600
         */
        void set_value_as_int(Glib::ustring,int);


        /**
         * @brief value getter for _default_ config value, use CONFIG_GET_DEFAULT(x) macro instead
         *
         * @param Glib::ustring, config option url as ustring
         *
         * @return default predefined option value as ustring
         */
        Glib::ustring get_default_value(Glib::ustring);


        /**
         * @brief int value getter for _default_ config value, use CONFIG_GET_DEFAULT_AS_INT(x) macro instead
         *
         * @param Glib::ustring, config option url as ustring
         *
         * @return default predefined option value as int
         */
        int get_default_value_as_int(Glib::ustring);


        /**
         * @brief writes _current_ configuration as config.xml file to hard disk, use CONFIG_SAVE_NOW() macro instead
         */
        void save_config_now();

    private:
        /*internal traversing funcs*/
        xmlNodePtr traverse(const char*, xmlNodePtr);
        xmlNodePtr _traverse(const char*, char*, char*, size_t, xmlNodePtr);

        /*model config member for data access*/
        Model cfgmodel;
        Glib::ustring _get_value(Glib::ustring, bool);
        int _get_value_as_int(Glib::ustring, bool);
    };
}

#define CONFIG_SET(x,y) Config::Handler::instance().set_value(x,y)
#define CONFIG_GET(x)   Config::Handler::instance().get_value(x)

#define CONFIG_SET_AS_INT(x,y) Config::Handler::instance().set_value_as_int(x,y)
#define CONFIG_GET_AS_INT(x)   Config::Handler::instance().get_value_as_int(x)

#define CONFIG_SAVE_NOW() Config::Handler::instance().save_config_now()

#define CONFIG_GET_DEFAULT(x) Config::Handler::instance().get_default_value(x)
#define CONFIG_GET_DEFAULT_AS_INT(x) Config::Handler::instance().get_default_value_as_int(x)

#endif /* end of include guard: Handler_89V106EN */
