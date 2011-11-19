#include "Statusbar.hh"
#include "../Log/Writer.hh"
#include "../Utils/Utils.hh"

#include <cstring>

#define MAX_TIME_BUF 42

namespace GManager
{
    Statusbar::Statusbar(ClientTimerProxy& tproxy, MPD::Client& client, const Glib::RefPtr<Gtk::Builder>& builder)
    {

        BUILDER_GET(builder,"statusbar",m_Statusbar);
        m_Statusbar->push("N/C");

        mp_Message = NULL;
        mp_Proxy = &tproxy;

        client.get_notify().connect(sigc::mem_fun(*this,&Statusbar::on_client_update));
        mp_Proxy->get_notify().connect(sigc::mem_fun(*this,&Statusbar::on_heartbeat));
    }

    /* ------------------ */

    Statusbar::~Statusbar(void)
    {
        g_free(mp_Message);
    }

    /* ------------------ */

    void Statusbar::format_time(unsigned time, char buffer[])
    {
        sprintf(buffer,"%d:%02d",time/60,time%60);
    }

    /* ------------------ */

    void Statusbar::on_client_update(enum mpd_idle event, MPD::NotifyData& data)
    {
        if(event & (MPD_IDLE_DATABASE | MPD_IDLE_OUTPUT | MPD_IDLE_PLAYER | MPD_IDLE_OPTIONS))
        {
            mp_Lastdata = &data;
            MPD::Status& status = data.get_status();
            mp_Proxy->set(status.get_elapsed_time());
            switch(status.get_state())
            {
                case MPD_STATE_PLAY:
                    mp_Proxy->play();
                    break;
                case MPD_STATE_STOP:
                case MPD_STATE_PAUSE:
                    mp_Proxy->pause();
                    break;
                case MPD_STATE_UNKNOWN:
                default:
                    break;
            }
            do_update_message(data);
        }
    }
    
    /* ------------------ */

    void Statusbar::on_heartbeat(double time)
    {
        do_update_message(*mp_Lastdata);
    }

    /* ------------------ */

    void Statusbar::do_update_message(MPD::NotifyData& data)
    {
            MPD::Status& status = data.get_status(); 
            MPD::Statistics& stats = data.get_statistics(); 

            char elapsed[MAX_TIME_BUF] = {0};
            char totaltm[MAX_TIME_BUF] = {0};

            format_time((unsigned)mp_Proxy->get(),elapsed);
            format_time(status.get_total_time(), totaltm);

            /* Free previous message, does nothing on NULL */
            g_free(mp_Message);

            unsigned long db_play_time = stats.get_db_play_time();
            unsigned long pt_days    = db_play_time / (60 * 60 * 24);
            unsigned long pt_hours   = (db_play_time / (60 * 60)) % pt_days;
            unsigned long pt_minutes = (db_play_time / 60) % pt_hours;
            unsigned long pt_seconds = db_play_time % 60;

            mp_Message = g_strdup_printf("%uHz | %ubit | %dkbit | %s | %s/%s | %u songs | %lu days %lu hours %lu:%lu total playtime",
                    status.get_audio_sample_rate(),
                    status.get_audio_bits(),
                    status.get_kbit_rate(),
                    status.get_audio_channels() == 1 ? "Mono" : "Stereo",
                    elapsed,
                    totaltm,
                    stats.get_number_of_songs(),
                    pt_days,pt_hours,pt_minutes,pt_seconds
                    );

            m_Statusbar->push(mp_Message);
    }
}
