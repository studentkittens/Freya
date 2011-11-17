#include "ClientTimerProxy.hh"

namespace GManager
{
    ClientTimerProxy::ClientTimerProxy(void) : signal_proxy()
    {
        timer = 0.0;
        count_up = true;
        
        Glib::signal_timeout().connect(sigc::mem_fun(*this,&ClientTimerProxy::on_interval),500);
    }

    // -------------
    
    ClientTimerProxy::~ClientTimerProxy(void)
    {}

    // -------------
    
    gboolean ClientTimerProxy::on_interval(void)
    {
        if(count_up)
        {
            timer += 0.5f;
            signal_proxy.emit(timer);
        }
        return TRUE;
    }

    // -------------
    
    void ClientTimerProxy::reset(void)
    {
        timer = 0.0;
    }

    // -------------

    void ClientTimerProxy::pause(void)
    {
        count_up = !count_up;
    }

    // -------------

    TimerNotifier& ClientTimerProxy::get_notify(void)
    {
        return signal_proxy;
    }
}
