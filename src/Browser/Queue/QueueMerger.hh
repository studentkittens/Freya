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


#ifndef FREYA_QUEUE_MERGER
#define FREYA_QUEUE_MERGER

#include "../../MPD/AbstractItemlist.hh"
#include "../../MPD/AbstractClientUser.hh"
#include "QueueModelColumns.hh"

#include <gtkmm.h>

namespace Browser
{
    /**
     * @brief This class manages the updating and merging of the Queue.
     *
     * When an update needs to be done, and it's not the first start, or
     * a serverchange, then fill_queue_changes() of MPD::Client is called,
     * and the changes are merged in.
     *
     * fill_queue_changes() delivers the correct list since the first position that changed.
     */
    class QueueMerger : public MPD::AbstractItemlist, public MPD::AbstractClientUser
    {
    public:
        QueueMerger(MPD::Client& client,
                    Glib::RefPtr<Gtk::ListStore>& queue_model,
                    QueueModelColumns& queue_columns);

        /**
         * @brief Implemented from AbstractItemlist
         *
         * @param pSong a MPD::Song
         */
        void add_item(MPD::AbstractComposite * pSong);

        /**
         * @brief Disables automatic updating 1x
         *
         * This is useful when for example some rows need to be deleted from the Queue.
         * Then, the rows are deleted from the model and the view, MPD is notified,
         * but the next update is disabled with this method.
         * Also positions in the row are calculated manually via recalculate_positions()
         */
        void disable_merge_once(void);
        /**
         * @brief Recalculate the position row of the Queue
         *
         * In order for merging to work all rows need to be in subsequent order.
         * This method rearranges the rows starting by pos or 0 if not given
         *
         * @param pos Where to start or 0 if not given
         */
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
        void on_connection_change(bool server_changed, bool is_connected);

        /**
         * @brief Set the contents of a single row
         *
         * @param row
         * @param pSong
         */
        void set_row_contents(Gtk::TreeModel::Row& row, MPD::Song * pSong);

        /**
         * @brief Add a row to the Queue
         *
         * @param pSong
         */
        void add_row(MPD::Song * pSong);

        /**
         * @brief merge (at the moment, just replace the row) a row
         *
         * @param pSong
         */
        void merge(MPD::Song * pSong);

        /**
         * @brief Remove all rows after this (including starting_with pos)
         *
         * @param starting_with
         */
        void trim(unsigned starting_with);


        /**
         * @brief Get a treemodel iter at position pos
         *
         * @param pos
         *
         * @return
         */
        Gtk::TreeModel::iterator get_iter_at_pos(int pos);

        /* -------------------- */

        bool mergeDisabled;
        bool mergeIterIsValid;
        bool m_ServerChanged;

        Gtk::TreeModel::iterator mergeIter;

        unsigned lastPlaylistVersion;
        unsigned playlistLength;
        unsigned mergePos;

        Glib::RefPtr<Gtk::ListStore> mp_QueueModel;
        QueueModelColumns * mp_QueueColumns;
    };
}

#endif /* end of include guard: FREYA_QUEUE_MERGER */
