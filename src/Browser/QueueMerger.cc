#include "QueueMerger.hh"
#include "../Log/Writer.hh"

namespace Browser
{
    QueueMerger::QueueMerger(MPD::Client& client, 
                             Glib::RefPtr<Gtk::ListStore>& queue_model,
                             QueueModelColumns& queue_columns) :
        AbstractClientUser(client),
        mergeDisabled(false),
        needsRefill(true),
        mergeIterIsValid(false),
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
        char int_buf[16] = {0};
        g_snprintf(int_buf,sizeof(int_buf),"%d",pos);
        return mp_QueueModel->get_iter(int_buf);
    }

    /*-------------------*/

    void QueueMerger::set_row_contents(Gtk::TreeModel::Row& row, MPD::Song * pSong)
    {
        row[mp_QueueColumns->m_col_id]  = pSong->get_id();
        row[mp_QueueColumns->m_col_pos] = pSong->get_pos();

        try { /* Check for NULLs just to be sure */
            row[mp_QueueColumns->m_col_title]  = pSong->get_tag(MPD_TAG_TITLE,0);
            row[mp_QueueColumns->m_col_album]  = pSong->get_tag(MPD_TAG_ALBUM,0);
            row[mp_QueueColumns->m_col_artist] = pSong->get_tag(MPD_TAG_ARTIST,0);
        } catch(const std::logic_error& e) {
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

    void QueueMerger::add_item(void * pSong)
    {
        g_assert(pSong);
        MPD::Song * new_song = (MPD::Song*)pSong;

        if(needsRefill)
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
                if(needsRefill)
                {
                    Info("Doing full refill of the queue.");
                    mp_QueueModel->clear();  
                    mp_Client->fill_queue(*this);

                    /* This usually only necessary on startup. */
                    needsRefill = false;
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

    void QueueMerger::on_connection_change(bool is_connected)
    {}

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