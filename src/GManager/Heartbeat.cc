 /***********************************************************
* This file is part of Freya 
* - A free MPD Gtk3 MPD Client -
* 
* Authors: Christopher Pahl, Christoph Piechula,
*          Eduard Schneider, Marc Tigges
*
* Copyright (C) [2011-2012]
* Hosted at: https://github.com/studentkittens/Freya
*
*              __..--''``---....___   _..._    __
*    /// //_.-'    .-/";  `        ``<._  ``.''_ `. / // /
*   ///_.-' _..--.'_                        `( ) ) // //
*   / (_..-' // (< _     ;_..__               ; `' / ///
*    / // // //  `-._,_)' // / ``--...____..-' /// / //  
*  Ascii-Art by Felix Lee <flee@cse.psu.edu>
*
* Freya is free software: you can redistribute it and/or modify
* it under the terms of the GNU General Public License as published by
* the Free Software Foundation, either version 3 of the License, or
* (at your option) any later version.
*
* Freya is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
* GNU General Public License for more details.
*
* You should have received a copy of the GNU General Public License
* along with Freya. If not, see <http://www.gnu.org/licenses/>.
**************************************************************/
#include "Heartbeat.hh"

#define INTERVAL 500/*ms*/
#define STEPSIZE (INTERVAL/1000.0)

namespace GManager
{
    Heartbeat::Heartbeat(MPD::Client& client) :
        AbstractClientUser(client),
        mp_LastNotifyData(NULL)
    {
        timer = 0.0;
        count_up = true;
    
        /* Timeout signal */    
        Glib::signal_timeout().connect(sigc::mem_fun(*this,&Heartbeat::on_interval),INTERVAL);
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

    TimerNotifier& Heartbeat::signal_client_update(void)
    {
        return signal_proxy;
    }
    
    // -------------
           
    void Heartbeat::on_connection_change(bool server_changed, bool is_connected)
    {
        if(is_connected && mp_LastNotifyData) 
            signal_proxy.emit(mp_LastNotifyData->get_status().get_elapsed_ms() / 1000.0);
        else
            pause();
    }
    
    // -------------
    
    /* Implemented from AbstractClientUser, but empty in this case */    
    void Heartbeat::on_client_update(enum mpd_idle event, MPD::NotifyData& data)
    {
        mp_LastNotifyData = &data;
        if(event & (MPD_IDLE_OUTPUT | MPD_IDLE_PLAYER | MPD_IDLE_OPTIONS))
        {
            MPD::Status& status = data.get_status();
            set(status.get_elapsed_ms() / 1000.0);
            switch(status.get_state())
            {
                case MPD_STATE_PLAY:
                    play();
                    break;
                case MPD_STATE_STOP:
                case MPD_STATE_PAUSE:
                    pause();
                    break;
                case MPD_STATE_UNKNOWN:
                default:
                    break;
            }
        }
    }
}
