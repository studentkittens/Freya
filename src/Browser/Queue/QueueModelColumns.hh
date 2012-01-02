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

#ifndef FREYA_QUEUEMODELCOLUMNS_GUARD
#define FREYA_QUEUEMODELCOLUMNS_GUARD

#include <gtkmm.h>

namespace Browser
{
    /**
     * @brief The Column Definition of Browser::Queue
     *
     * This is a separate (as opposed to a local nested class) because
     * it is also needed by Browser::QueueMerger
     */
    class QueueModelColumns : public Gtk::TreeModel::ColumnRecord
    {
    public:

        QueueModelColumns();

        /**
         * @brief The ID of the Song
         *
         * Needed for some commands
         */
        Gtk::TreeModelColumn<unsigned>      m_col_id;
        /**
         * @brief The Position of the Song in the Queue
         *
         * Needed for some commands and for merging
         */
        Gtk::TreeModelColumn<unsigned>      m_col_pos;
        /**
         * @brief Titlestring
         */
        Gtk::TreeModelColumn<Glib::ustring> m_col_title;
        /**
         * @brief Albumstring
         */
        Gtk::TreeModelColumn<Glib::ustring> m_col_album;
        /**
         * @brief Artiststring
         */
        Gtk::TreeModelColumn<Glib::ustring> m_col_artist;
    };
}

#endif /* end of include guard: FREYA_QUEUEMODELCOLUMNS_GUARD */
