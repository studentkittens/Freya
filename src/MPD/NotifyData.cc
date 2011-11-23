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
    // TODO: Unclutter.
    //------------------
 
    void NotifyData::update_status(void)
    {
        if(mp_Status != NULL)
        {
            delete mp_Status;
            mp_Status = NULL;
        }

        mpd_status * c_status = mpd_run_status(mp_Conn->get_connection());
        if(c_status != NULL)
        {
            mp_Status = new Status(*c_status);
        }
        else
        {
            Warning("Got an empty status, although being connected!");
        }
    }
    
    //------------------
   
    Status& NotifyData::get_status(void)
    {
        return *(mp_Status);
    } 

    //------------------

    void NotifyData::update_statistics(void)
    {
        if(mp_Statistics != NULL)
        {
            delete mp_Statistics;
            mp_Statistics = NULL;
        }

        mpd_stats * c_stats = mpd_run_stats(mp_Conn->get_connection());
        if(c_stats != NULL)
        {
            mp_Statistics = new Statistics(*c_stats);
        }
        else
        {
            Warning("Got empty statistics, although being connected!");
        }
    }
    
    //------------------
   
    Statistics& NotifyData::get_statistics(void)
    {
        return *(mp_Statistics);
    } 

    //------------------

    void NotifyData::update_song(void)
    {
        if(mp_Song != NULL)
        {
            delete mp_Song;
            mp_Song = NULL;
        }

        mpd_song * c_song = mpd_run_current_song(mp_Conn->get_connection());
        if(c_song != NULL)
        {
            mp_Song = new Song(*c_song);
        }
        else
        {
            Warning("Got empty song, although being connected!");
        }
    }
    
    //------------------
   
    Song& NotifyData::get_song(void)
    {
        return *(mp_Song);
    } 
    
    //------------------

    void NotifyData::update_all(void)
    {
       // mpd_command_list_begin(mp_Conn->get_connection(),false);
        update_status();
        update_statistics();
        update_song();
       // mpd_command_list_end(mp_Conn->get_connection());
    }
}
