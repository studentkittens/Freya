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

#ifndef FREYA_ABSTRACTITEM_GENERATOR
#define FREYA_ABSTRACTITEM_GENERATOR

#include "AbstractItemlist.hh"

/**
 * @brief This class exists to allow use of the Proxy Pattern (i.e. a Proxy for MPD::Client)
 *
 * Instead of talking directly with the client in order to request data some classes want to
 * do implement something own, like for example a caching of the data.
 *
 * An example would be the DatabaseCache that implements this class. It caches all data,
 * and requests data only if not cached yet.
 */
namespace MPD
{
    class AbstractItemGenerator
    {
    public:
        virtual void fill_queue(AbstractItemlist& data_model) = 0;
        virtual void fill_queue_changes(AbstractItemlist& data_model, unsigned last_version, unsigned& first_pos) = 0;
        virtual void fill_playlists(AbstractItemlist& data_model) = 0;
        virtual void fill_outputs(AbstractItemlist& data_model) = 0;
        virtual void fill_filelist(AbstractItemlist& data_model, const char * path) = 0;

        virtual ~AbstractItemGenerator() {};
    };
}

#endif /* end of include guard: FREYA_ABSTRACTITEM_GENERATOR */
