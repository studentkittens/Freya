#include "Heartbeat.hh"

#define INTERVAL 500//ms
#define STEPSIZE (INTERVAL/1000.0)

namespace GManager
{
    Heartbeat::Heartbeat(MPD::Client& client) : signal_proxy()
    {
        timer = 0.0;
        count_up = true;
        
        Glib::signal_timeout().connect(sigc::mem_fun(*this,&Heartbeat::on_interval),INTERVAL);
        client.signal_connection_change().connect(sigc::mem_fun(*this,&Heartbeat::on_connection_change));
    }

    // -------------
    
    Heartbeat::~Heartbeat(void)
    {}

    // -------------
    
    gboolean Heartbeat::on_interval(void)
    {
        if(count_up)
        {
            timer += STEPSIZE; 
            signal_proxy.emit(timer);
        }
        return TRUE;
    }

    // -------------
    
    void Heartbeat::reset(void)
    {
        timer = 0.0;
    }

    // -------------

    void Heartbeat::pause(void)
    {
        count_up = false;
    }

    // -------------
    
    void Heartbeat::play(void)
    {
        count_up = true;
    }

    // -------------
    
    void Heartbeat::set(double val)
    {
        timer = val;
    }
     
    // -------------
    
    double Heartbeat::get(void)
    {
        return timer;
    }

    // -------------

    TimerNotifier& Heartbeat::get_notify(void)
    {
        return signal_proxy;
    }
           
    void Heartbeat::on_connection_change(bool is_connected)
    {
        if(is_connected) 
            play();
        else
            pause();
    }
}
