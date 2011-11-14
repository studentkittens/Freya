#include "Statusbar.hh"
#include "../Log/Writer.hh"

#include <cstring>

#define MAX_TIME_BUF 42

namespace GManager
{
    Statusbar::Statusbar(MPD::Client& client, const Glib::RefPtr<Gtk::Builder>& builder)
    {
        client.get_notify().connect(sigc::mem_fun(*this,&Statusbar::on_client_update));

        try
        {
            builder->get_widget("statusbar",m_Statusbar);
            Gtk::manage(m_Statusbar);
            m_Statusbar->push("N/C");
            mp_Message = NULL;
        }
        catch(const Gtk::BuilderError& e)
        {
            Error("BuilderFailure: %s",e.what().c_str());
        }
    }

    /* ------------------ */

    Statusbar::~Statusbar(void)
    {
        g_free(mp_Message);
    }
    
    /* ------------------ */

    void Statusbar::format_time(unsigned time, char buffer[])
    {
        sprintf(buffer,"%d:%d",time/60,time%60);
    }

    /* ------------------ */

    void Statusbar::on_client_update(enum mpd_idle, MPD::NotifyData& data)
    {
        mp_Lastdata = &data;
        MPD::Status& status = data.get_status(); 

        char elapsed[MAX_TIME_BUF] = {0};
        char totaltm[MAX_TIME_BUF] = {0};

        format_time(status.get_elapsed_time(),elapsed);
        format_time(status.get_total_time(), totaltm);

        g_free(mp_Message);
        mp_Message = g_strdup_printf("%uHz | %ubit | %dkbit | %s | %s/%s | songs_in_db | playtime_in_total",
                status.get_audio_sample_rate(),
                status.get_audio_bits(),
                status.get_kbit_rate(),
                status.get_audio_channels() == 1 ? "Mono" : "Stereo",
                elapsed,
                totaltm
                );

        m_Statusbar->push(mp_Message);
    }
}
