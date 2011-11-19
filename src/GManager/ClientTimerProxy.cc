#include "ClientTimerProxy.hh"

#define INTERVAL 500//ms
#define STEPSIZE (INTERVAL/1000.0)

namespace GManager
{
    ClientTimerProxy::ClientTimerProxy(void) : signal_proxy()
    {
        timer = 0.0;
        count_up = true;
        
        Glib::signal_timeout().connect(sigc::mem_fun(*this,&ClientTimerProxy::on_interval),INTERVAL);
    }

    // -------------
    
    ClientTimerProxy::~ClientTimerProxy(void)
    {}

    // -------------
    
    gboolean ClientTimerProxy::on_interval(void)
    {
        if(count_up)
        {
            timer += STEPSIZE; 
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
        count_up = false;
    }

    // -------------
    
    void ClientTimerProxy::play(void)
    {
        count_up = true;
    }

    // -------------
    
    void ClientTimerProxy::set(double val)
    {
        timer = val;
    }
     
    // -------------
    
    double ClientTimerProxy::get(void)
    {
        return timer;
    }

    // -------------

    TimerNotifier& ClientTimerProxy::get_notify(void)
    {
        return signal_proxy;
    }
}
