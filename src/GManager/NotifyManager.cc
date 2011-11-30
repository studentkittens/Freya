#include "NotifyManager.hh"

namespace GManager
{
    NotifyManager::NotifyManager(MPD::Client& client) :
        AbstractGElement(client)
    {
    }

    void NotifyManager::on_client_update(enum mpd_idle event, MPD::NotifyData& data)
    {

    }

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

}
