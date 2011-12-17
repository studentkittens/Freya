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


#ifndef FREYA_QUEUE_MERGER
#define FREYA_QUEUE_MERGER

#include "../MPD/AbstractItemlist.hh"
#include "../MPD/AbstractClientUser.hh"
#include "QueueModelColumns.hh"

#include <gtkmm.h>

namespace Browser 
{
    class QueueMerger : public AbstractItemlist, public AbstractClientUser
    {
        public:
            QueueMerger(MPD::Client& client,
                        Glib::RefPtr<Gtk::ListStore>& queue_model,
                        QueueModelColumns& queue_columns);

            /**
             * @brief 
             *
             * @param pSong
             */
            void add_item(void * pSong);

            void disable_merge_once(void);
            void recalculate_positions(unsigned pos = 0);

        private:
            
            /**
             * @brief Implemented from AbstractClientUser
             *
             * @param event
             * @param data
             */
            void on_client_update(mpd_idle event, MPD::NotifyData& data);

            /**
             * @brief Implemented from AbstractClientUser
             *
             * @param is_connected
             */
            void on_connection_change(bool is_connected);

            /**
             * @brief Set the contents of a single row
             *
             * @param row
             * @param pSong
             */
            void set_row_contents(Gtk::TreeModel::Row& row, MPD::Song * pSong);

            void add_row(MPD::Song * pSong);

            void merge(MPD::Song * pSong);

            void trim(unsigned starting_with);


            Gtk::TreeModel::iterator get_iter_at_pos(int pos);

            /* -------------------- */

            bool mergeDisabled;
            bool needsRefill;
            bool mergeIterIsValid;
            bool wasReconnected;

            Gtk::TreeModel::iterator mergeIter;

            unsigned lastPlaylistVersion;
            unsigned playlistLength;
            unsigned mergePos;

            Glib::RefPtr<Gtk::ListStore> mp_QueueModel;
            QueueModelColumns * mp_QueueColumns;
    };
}

#endif /* end of include guard: FREYA_QUEUE_MERGER */
