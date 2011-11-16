#include "Statusbar.hh"
#include "../Log/Writer.hh"
#include "../Utils/Utils.hh"

#include <cstring>

#define MAX_TIME_BUF 42

namespace GManager
{
    Statusbar::Statusbar(MPD::Client& client, const Glib::RefPtr<Gtk::Builder>& builder)
    {
        client.get_notify().connect(sigc::mem_fun(*this,&Statusbar::on_client_update));
        BUILDER_GET(builder,"statusbar",m_Statusbar);
        m_Statusbar->push("N/C");
        mp_Message = NULL;
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
        MPD::Statistics& stats = data.get_statistics(); 

        char elapsed[MAX_TIME_BUF] = {0};
        char totaltm[MAX_TIME_BUF] = {0};

        format_time(status.get_elapsed_time(),elapsed);
        format_time(status.get_total_time(), totaltm);

        /* Free previous message, does nothing on NULL */
        g_free(mp_Message);

        mp_Message = g_strdup_printf("%uHz | %ubit | %dkbit | %s | %s/%s | %u | %lu",
                status.get_audio_sample_rate(),
                status.get_audio_bits(),
                status.get_kbit_rate(),
                status.get_audio_channels() == 1 ? "Mono" : "Stereo",
                elapsed,
                totaltm,
                stats.get_number_of_songs(),
                stats.get_db_play_time()
                );

        m_Statusbar->push(mp_Message);
    }
}
