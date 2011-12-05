#include "NotifyData.hh"
#include "../Log/Writer.hh"

namespace MPD
{
    NotifyData::NotifyData(MPD::Connection& p_conn)
    {
        mp_Conn = &p_conn; 
        mp_Status = NULL;
        mp_Statistics = NULL;
        mp_Song = NULL;
        mp_NextSong = NULL;
    }

    //------------------

    NotifyData::~NotifyData(void) 
    {
        delete mp_Statistics;
        delete mp_Status;
        delete mp_Song;
        delete mp_NextSong;
    }

    //------------------

    /* Since libmpdclient does not support the next-song-id,
     * we habe to improvise a little bit. 
     */
    Status * NotifyData::recv_status_own(void)
    {
        struct mpd_status * status = NULL;
        struct mpd_connection * conn = NULL;
        struct mpd_pair *pair = NULL;
        Status * retv_status = NULL;
        unsigned long NextSongID = 0;

        if(mp_Conn->is_connected())
        {
            conn = mp_Conn->get_connection();
            mpd_send_status(conn);
            status = mpd_status_begin();
            if(status != NULL) 
            {
                while ((pair = mpd_recv_pair(conn)) != NULL) 
                {
                    if(!g_ascii_strcasecmp(pair->name,"nextsongid"))
                    {
                        NextSongID = g_ascii_strtoll(pair->value,NULL,10);
                    }
                    else
                    {
                        mpd_status_feed(status, pair);
                    }
                    mpd_return_pair(conn, pair);
                }
            }

            if(status != NULL)
            {
                retv_status = new Status(*status,NextSongID);
            }
                
            if(mp_NextSong != NULL) {
                delete mp_NextSong;
                mp_NextSong = NULL;
            }

            mpd_song * c_next_song = mpd_run_get_queue_song_id(conn,NextSongID);
            if(c_next_song != NULL)
            {
                mp_NextSong = new Song(*c_next_song);
            }
            else
            {
                mp_Conn->clear_error();
            }
        }
        return retv_status;
    }

    //------------------

    Status& NotifyData::get_status(void)
    {
        /* This should never be NULL. */
        g_assert(mp_Status);
        return *(mp_Status);
    } 

    //------------------

    Statistics& NotifyData::get_statistics(void)
    {
        /* This should never be NULL. */
        g_assert(mp_Statistics);
        return *(mp_Statistics);
    } 

    //------------------

    Song * NotifyData::get_song(void)
    {
        return mp_Song;
    } 

    //------------------

    Song * NotifyData::get_next_song(void)
    {
        return mp_NextSong;
    } 

    //------------------

    void NotifyData::update_all(void)
    {
        if(mp_Song != NULL) {
            delete mp_Song;
            mp_Song = NULL;
        }

        if(mp_Statistics != NULL) {
            delete mp_Statistics;
            mp_Statistics = NULL;
        }

        if(mp_Status != NULL) {
            delete mp_Status;
            mp_Status = NULL;
        }

        if(mp_Conn->is_connected())
        {
            mpd_connection * mpd_conn = mp_Conn->get_connection();
            mpd_song * c_song = NULL;
            mpd_stats * c_stats = NULL;

            c_song   = mpd_run_current_song(mpd_conn);
            c_stats  = mpd_run_stats(mpd_conn);

            if(c_song)   mp_Song = new Song(*c_song);
            if(c_stats)  mp_Statistics = new Statistics(*c_stats);
            mp_Status = recv_status_own();

            /* Pray that this will never happen. */
            if(!(mp_Status && c_stats))
                Error("Status/Song/Statistic is empty although being connected. Prepare for a crash.");
        }
    }
}
