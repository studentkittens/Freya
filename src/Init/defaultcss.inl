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

#ifndef FREYA_DEFAULTCSS_GUARD
#define FREYA_DEFAULTCSS_GUARD
#include <glibmm/ustring.h>

namespace Init
{
    static const Glib::ustring defaultcss_inl(
            "/* Freya CSS overlay                      \n"
            " *                                        \n"
            " * Note: This is not overwritte by Freya, \n"
            " *       but sometimes updates may needed \n"
            " */                                       \n"
            "GtkNotebook {                             \n"
            "    color: #999999;                       \n"
            "    background-color: #000000;            \n"
            "    border-width: 0;                      \n"
            "    border-radius: 0;                     \n"
            "    border-color: #000000;                \n"
            "    margin: 0;                            \n"
            "}                                         \n"
            "                                          \n"
            "GtkTextView {                             \n"
            "    color: #999999;                       \n"
            "    background-color: rgba(0,0,0,0);      \n"
            "}                                         \n"
            "                                          \n"
            "GtkNotebook GtkLabel {                    \n"
            "    color: #000000;                       \n"
            "}                                         \n"
            );
}

#endif
