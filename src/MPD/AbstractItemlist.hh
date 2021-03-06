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
#ifndef FREYA_ABSTRACT_SONGLIST_GUARD
#define FREYA_ABSTRACT_SONGLIST_GUARD

#include "AbstractComposite.hh"

namespace MPD
{
/**
 * @brief Inhertit from this class to use MPD::Client's fill_* methods.
 */
class AbstractItemlist
{
public:

    /**
     * @brief Called after calling (e.g.) fill_queue()
     *
     * Cast this to the correct type, fill_queue delivers you for example a MPD::Song*
     *
     * @param item a dynamically allocated item
     */
    virtual void add_item(MPD::AbstractComposite * item) = 0;


    /**
     * @brief Virtual DTor so, derived class call their own DTor
     */
    virtual ~AbstractItemlist() {};
};
}

#endif
