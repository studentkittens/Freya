#include "Timeslide.hh"
#include "../Log/Writer.hh"
#include "../Utils/Utils.hh"

#define UPDATE_TIMEOUT 0.1

namespace GManager
{
    Timeslide::Timeslide(Heartbeat& tproxy, MPD::Client& client, const Glib::RefPtr<Gtk::Builder>& builder) :
        AbstractClientUser(client),
        m_Timeguard()
    {
        mp_Proxy  = &tproxy;
        ignore_signal = false;

        BUILDER_GET(builder,"time_slide",m_Timeslide);
        m_Timeslide->set_range(0.0,100.0);

        m_Timeslide->signal_value_changed().connect(sigc::mem_fun(*this,&Timeslide::on_user_action));
        tproxy.get_notify().connect(sigc::mem_fun(*this,&Timeslide::tick));
    }

    /* ------------------ */

    void Timeslide::tick(double time)
    {
        ignore_signal = true;
        m_Timeslide->set_value(time);
        ignore_signal = false;
    }
    
    /* ------------------ */

    void Timeslide::on_user_action(void)
    {
        /* only allow updates every 0.1 seconds */
        if(!ignore_signal && m_Timeguard.elapsed() > UPDATE_TIMEOUT)
        {
            double new_value = m_Timeslide->get_value();
            if(mp_Client->is_connected())
            {
                unsigned song_id = mp_Client->get_status()->get_song_id();
                mp_Client->playback_seek(song_id,new_value);
            }
            mp_Proxy->set(new_value);
            m_Timeguard.reset();
        }
    }

    /* ------------------ */
    
    void Timeslide::on_connection_change(bool is_connected)
    {
        m_Timeslide->set_sensitive(is_connected);
    }

    /* ------------------ */

    void Timeslide::on_client_update(enum mpd_idle event, MPD::NotifyData& data)
    {
        if(!ignore_signal && event & (MPD_IDLE_PLAYER))
        {
            MPD::Status& status = data.get_status();

            ignore_signal = true;
            m_Timeslide->set_range(0.0,status.get_total_time());
            m_Timeslide->set_value(status.get_elapsed_time());
            mp_Proxy->set(status.get_elapsed_time());
            ignore_signal = false;

            switch(data.get_status().get_state())
            {
                case MPD_STATE_STOP:
                    mp_Proxy->reset();
                    break;
                case MPD_STATE_PAUSE:
                    mp_Proxy->pause();
                    break;
                case MPD_STATE_PLAY:
                    mp_Proxy->play();
                    break;
                case MPD_STATE_UNKNOWN:
                default:
                    break;
            }
        }
    }
}
