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
    }

    //------------------

    NotifyData::~NotifyData(void) 
    {
        delete mp_Statistics;
        delete mp_Status;
        delete mp_Song;
    }

    //------------------
   
    Status& NotifyData::get_status(void)
    {
        return *(mp_Status);
    } 

    //------------------
   
    Statistics& NotifyData::get_statistics(void)
    {
        return *(mp_Statistics);
    } 

    //------------------
    
    Song& NotifyData::get_song(void)
    {
        return *(mp_Song);
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
            mpd_status * c_status = NULL;

            // actually this is supposed to work.. wtf.
            // rc &= mpd_command_list_begin(mpd_conn,true);
            /*
            bool rc = true;
            rc &= mpd_send_status(mpd_conn);
            c_status = mpd_recv_status(mpd_conn);
            rc &= mpd_send_current_song(mpd_conn);
            c_song   = mpd_recv_song(mpd_conn);
            rc &= mpd_send_stats(mpd_conn);
            c_stats  = mpd_recv_stats(mpd_conn);
            */
            //rc &= mpd_command_list_end(mpd_conn);
            
            c_status = mpd_run_status(mpd_conn);
            c_song = mpd_run_current_song(mpd_conn);
            c_stats = mpd_run_stats(mpd_conn);

            if(c_song)   mp_Song = new Song(*c_song);
            if(c_status) mp_Status = new Status(*c_status);
            if(c_stats)  mp_Statistics = new Statistics(*c_stats);

            /* Pray that this will never happen. */
            if(!(c_song && c_status && c_stats))
                Error("Status/Song/Statistic is empty although being connected. Prepare for a crash.");
        }
    }
}
