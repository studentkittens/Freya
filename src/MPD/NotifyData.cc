#include "NotifyData.hh"
#include "../Log/Writer.hh"

namespace MPD
{
    NotifyData::NotifyData(MPD::Connection& p_conn)
    {
       mp_Conn = &p_conn; 
       mp_Status = NULL;
    }

    //------------------

    NotifyData::~NotifyData(void) 
    {
        delete mp_Status;
    }

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
}
