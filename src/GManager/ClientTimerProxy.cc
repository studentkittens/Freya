#include "ClientTimerProxy.hh"

namespace GManager
{
    ClientTimerProxy::ClientTimerProxy(MPD::Client& client) : signal_proxy()
    {
        mp_Client = &client;
        mp_Data = NULL;
        mp_Event = (enum mpd_idle)0;

        mp_Client->get_notify().connect(sigc::mem_fun(*this,&ClientTimerProxy::on_client_update));
        Glib::signal_timeout().connect(sigc::mem_fun(*this,&ClientTimerProxy::on_interval),500);
    }

    ClientTimerProxy::~ClientTimerProxy(void)
    {}

    gboolean ClientTimerProxy::on_interval(void)
    {
        if(mp_Client->is_connected() && mp_Data && mp_Event)
        {
            g_printerr("Tick.");
            mp_Client->force_update();
            //on_client_update(mp_Event,*mp_Data);
        }
        return TRUE;     
    }

    void ClientTimerProxy::on_client_update(enum mpd_idle event, MPD::NotifyData& data)
    {
            g_printerr("Tack.");
        mp_Data = &data;
        mp_Event = event;
        signal_proxy.emit(mp_Event,*mp_Data); 
    }

    EventNotifier& ClientTimerProxy::get_notify(void)
    {
        return signal_proxy;
    }
}
