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


#include "QueueMerger.hh"
#include "../../Log/Writer.hh"
#include "../../Utils/Utils.hh"

namespace Browser
{
    QueueMerger::QueueMerger(MPD::Client& client,
                             Glib::RefPtr<Gtk::ListStore>& queue_model,
                             QueueModelColumns& queue_columns) :
        AbstractClientUser(client),
        mergeDisabled(false),
        mergeIterIsValid(false),
        m_ServerChanged(true),
        isFirstStart(true),
        lastPlaylistVersion(0),
        playlistLength(0),
        mergePos(0),
        mp_QueueModel(queue_model),
        mp_QueueColumns(&queue_columns)
    {}

    /*-------------------*/

    void QueueMerger::disable_merge_once(void)
    {
        mergeDisabled = true;
    }

    /*-------------------*/

    Gtk::TreeModel::iterator QueueMerger::get_iter_at_pos(int pos)
    {
        return mp_QueueModel->get_iter(Utils::int_to_string(pos));
    }

    /*-------------------*/

    void QueueMerger::set_row_contents(Gtk::TreeModel::Row& row, MPD::Song * pSong)
    {
        row[mp_QueueColumns->m_col_id]  = pSong->get_id();
        row[mp_QueueColumns->m_col_pos] = pSong->get_pos();

        try
        {
            row[mp_QueueColumns->m_col_title]  = pSong->get_tag(MPD_TAG_TITLE,0);
            row[mp_QueueColumns->m_col_album]  = pSong->get_tag(MPD_TAG_ALBUM,0);
            row[mp_QueueColumns->m_col_artist] = pSong->get_tag(MPD_TAG_ARTIST,0);
        }
        catch(const std::logic_error& e)
        {
            Warning("Empty column: %s",e.what());
        }
    }

    /*-------------------*/

    void QueueMerger::add_row(MPD::Song * pSong)
    {
        Gtk::TreeModel::Row row = *(mp_QueueModel->append());
        set_row_contents(row,pSong);
    }

    /*-------------------*/

    void QueueMerger::merge(MPD::Song * pSong)
    {
        /* TODO: Better/more network efficient merging? */
        Gtk::TreeRow row = (*mergeIter);
        set_row_contents(row,pSong);
    }

    /*-------------------*/

    void QueueMerger::trim(unsigned starting_with)
    {
        Gtk::TreeModel::iterator iter = get_iter_at_pos(starting_with);
        while(iter)
        {
            iter = mp_QueueModel->erase(iter);
        }
    }

    /*-------------------*/

    void QueueMerger::add_item(MPD::AbstractComposite * pSong)
    {
        g_assert(pSong);
        MPD::Song * new_song = static_cast<MPD::Song*>(pSong);

        if(m_ServerChanged)
        {
            add_row(new_song);
        }
        else if(mergePos < playlistLength)
        {
            if(!mergeIterIsValid)
            {
                mergeIter = get_iter_at_pos(mergePos);
                mergeIterIsValid = (mergeIter);
            }

            if(mergeIterIsValid)
            {
                merge(new_song);
                mergePos++;
                mergeIter++;
            }
        }
        else
        {
            add_row(new_song);
        }

        delete new_song;
    }

    /*-------------------*/

    void QueueMerger::on_client_update(mpd_idle event, MPD::NotifyData& data)
    {
        if(event & MPD_IDLE_QUEUE)
        {
            if(!mergeDisabled)
            {
                MPD::Status& status = data.get_status();
                unsigned qu_v = status.get_queue_version();
                unsigned qu_l = status.get_queue_length();

                /* Do a full refill if requested (e.g. on startup) */
                if(m_ServerChanged || isFirstStart)
                {
                    Info("Doing full refill of the queue.");
                    mp_QueueModel->clear();
                    mp_Client->fill_queue(*this);
                    m_ServerChanged = false;
                }
                else
                {
                    /* Merge in changes */
                    mergeIterIsValid = false;
                    mp_Client->fill_queue_changes(*this,lastPlaylistVersion,mergePos);

                    /* Remove old items at end of list */
                    if(qu_l < playlistLength)
                        trim(qu_l);
                }

                lastPlaylistVersion = qu_v;
                playlistLength = qu_l;
            }
            mergeDisabled = false;
        }
    }

    /*-------------------*/

    void QueueMerger::on_connection_change(bool server_changed, bool is_connected)
    {
        /* This is also true on startup */
        m_ServerChanged = isFirstStart ? false : server_changed; 
        isFirstStart = false;
    }

    /*-------------------*/

    void QueueMerger::recalculate_positions(unsigned pos)
    {
        for(Gtk::TreeModel::iterator iter = get_iter_at_pos(pos); iter; iter++)
        {
            (*iter)[mp_QueueColumns->m_col_pos] = pos++;
        }
    }

    /*-------------------*/
}
