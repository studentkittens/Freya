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
            MPD::Song& current_song = data.get_song();
            MPD::Status& status = data.get_status();

            char * title_notify = g_markup_printf_escaped("%s (Track %s)",
                    current_song.get_tag(MPD_TAG_TITLE,0),
                    current_song.get_tag(MPD_TAG_TRACK,0)
                    );
            char * artist_notify = g_markup_printf_escaped("by %s on %s (%s)",
                    current_song.get_tag(MPD_TAG_ARTIST,0),
                    current_song.get_tag(MPD_TAG_ALBUM,0),
                    current_song.get_tag(MPD_TAG_DATE,0)
                    );

            if((status.get_state() == MPD_STATE_PLAY))
                NOTIFY_STOCK_ICON("media-playback-start");
            else if((status.get_state() == MPD_STATE_STOP))
                NOTIFY_STOCK_ICON("media-playback-stop");
            else if((status.get_state() == MPD_STATE_PAUSE))
                NOTIFY_STOCK_ICON("media-playback-pause");

            NOTIFY_SEND(title_notify,artist_notify);

            g_free(title_notify);
            g_free(artist_notify);
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
