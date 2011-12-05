#include "NotifyManager.hh"

namespace GManager
{
    NotifyManager::NotifyManager(MPD::Client& client) :
        AbstractClientUser(client)
    {
        /* Everything by AbstractClientUser already */
    }

    // ------------------------------------

    void NotifyManager::on_client_update(enum mpd_idle event, MPD::NotifyData& data)
    { 
        if(event & MPD_IDLE_PLAYER)
        {
            MPD::Song * current_song = data.get_song();
            if(current_song != NULL)
            {
                MPD::Status& status = data.get_status();

                if((status.get_state() == MPD_STATE_PLAY))
                    NOTIFY_STOCK_ICON("media-playback-start");
                else if((status.get_state() == MPD_STATE_STOP))
                    NOTIFY_STOCK_ICON("media-playback-stop");
                else if((status.get_state() == MPD_STATE_PAUSE))
                    NOTIFY_STOCK_ICON("media-playback-pause");

                NOTIFY_SEND(current_song->song_format("${title} (Track ${track})",false),current_song->song_format("by ${artist} on ${album} (${date})",false));

            }
        }
    }

    // ------------------------------------

    void NotifyManager::on_connection_change(bool is_connected)
    {
        NOTIFY_EXTRA();
        if(is_connected)
        {
            NOTIFY_STOCK_ICON("network-idle");
            NOTIFY_SEND("","Freya conntected!");
        }
        else
        {
            NOTIFY_STOCK_ICON("network-error");
            NOTIFY_SEND("","Freya disconnected!");
        }
    }

    // ------------------------------------

}
