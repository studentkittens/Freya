#include "Statusbar.hh"
#include "../Log/Writer.hh"
#include "../Utils/Utils.hh"

#define MAX_TIME_BUF 42

namespace GManager
{
    Statusbar::Statusbar(Heartbeat& tproxy, MPD::Client& client, const Glib::RefPtr<Gtk::Builder>& builder) :
        AbstractGElement(client)
    {
        BUILDER_GET(builder,"statusbar",m_Statusbar);

        mp_Message = NULL;
        mp_Lastdata = NULL;
        mp_Heartbeat = &tproxy;

        mp_Heartbeat->get_notify().connect(sigc::mem_fun(*this,&Statusbar::on_heartbeat));
    }

    /* ------------------ */

    Statusbar::~Statusbar(void)
    {
        g_free(mp_Message);
    }

    /* ------------------ */
    
    void Statusbar::on_connection_change(bool is_connected)
    {
       if(is_connected == false)
          mp_Lastdata = NULL; 
    }
    
    /* ------------------ */

    void Statusbar::format_time(unsigned time, char buffer[])
    {
        g_sprintf(buffer,"%d:%02d",time/60,time%60);
    }

    /* ------------------ */

    void Statusbar::on_client_update(enum mpd_idle event, MPD::NotifyData& data)
    {
        if(event & (MPD_IDLE_DATABASE | MPD_IDLE_OUTPUT | MPD_IDLE_PLAYER | MPD_IDLE_OPTIONS))
        {
            mp_Lastdata = &data;
            MPD::Status& status = data.get_status();
            mp_Heartbeat->set(status.get_elapsed_time());
            switch(status.get_state())
            {
                case MPD_STATE_PLAY:
                    mp_Heartbeat->play();
                    break;
                case MPD_STATE_STOP:
                case MPD_STATE_PAUSE:
                    mp_Heartbeat->pause();
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
        if(mp_Lastdata != NULL)
        {
            do_update_message(*mp_Lastdata);
        }
    }

    /* ------------------ */

    void Statusbar::do_update_message(MPD::NotifyData& data)
    {
            MPD::Status& status = data.get_status(); 
            MPD::Statistics& stats = data.get_statistics(); 

            char elapsed[MAX_TIME_BUF] = {0};
            char totaltm[MAX_TIME_BUF] = {0};

            format_time((unsigned)mp_Heartbeat->get(),elapsed);
            format_time(status.get_total_time(), totaltm);

            /* Free previous message, does nothing on NULL */
            g_free(mp_Message);

            Glib::ustring db_play_time = Utils::seconds_to_duration(stats.get_db_play_time());

            mp_Message = g_strdup_printf("%uHz | %ubit | %dkbit | %s | %s/%s | %u songs | %s total playtime | %u%% volume",
                    status.get_audio_sample_rate(),
                    status.get_audio_bits(),
                    status.get_kbit_rate(),
                    status.get_audio_channels() == 1 ? "Mono" : "Stereo",
                    elapsed,
                    totaltm,
                    stats.get_number_of_songs(),
                    db_play_time.c_str(),
                    CLAMP(status.get_volume(),0,100)
                    );

            m_Statusbar->set_text(mp_Message);
    }
}
