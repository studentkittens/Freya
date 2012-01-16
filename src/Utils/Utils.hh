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
#ifndef FREYA_UTILS_GUARD
#define FREYA_UTILS_GUARD

#include <glibmm.h>

/* For Error() */
#include "../Log/Writer.hh"

/* Gtk::Builder macros */
#define BUILDER_GET(builder_refp, widget_name, widget_ptr) \
    BUILDER_GET_NO_MANAGE(builder_refp, widget_name, widget_ptr) \
    Gtk::manage(widget_ptr);

#define BUILDER_GET_NO_MANAGE(builder_refp, widget_name, widget_ptr) \
    widget_ptr = NULL;                                     \
    builder_refp->get_widget(widget_name,widget_ptr);      \
    g_assert(widget_ptr);                                  \
 

#define BUILDER_ADD(builder_ref, filename)   \
    g_assert(filename);                      \
    try {                                    \
     builder_ref->add_from_file(filename);   \
    } catch(const Gtk::BuilderError& e) {    \
     Error("Could not add playlist ui"       \
           "definitions to builder. => %s"   \
           "| Is '%s' there and okay?",      \
           e.what().c_str(),filename);       \
    }
namespace Utils
{

    /**
     * @brief converts a given time in seconds to a duration ustring
     *
     * @param long, duration in seconds to convert
     *
     * @return duration as ustring, e.g. "4 hours 2 minutes 0 seconds"
     */
    Glib::ustring seconds_to_duration(unsigned long);


    /**
     * @brief converts a given time in seconds to a "timestamp"
     *
     * @param long, duration in seconds to convert
     *
     * @return date as ustring, e.g. 2011-04-02
     */
    Glib::ustring seconds_to_timestamp(const long);


    /**
     * @brief Simply converts any integer to a std::string
     *
     * @param num the integer
     *
     * @return a std::string containing just the number (copy for further use!)
     */
    std::string int_to_string(int num);
}
#endif
