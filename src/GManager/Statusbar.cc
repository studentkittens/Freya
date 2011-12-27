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
#include "Statusbar.hh"
#include "../Log/Writer.hh"
#include "../Utils/Utils.hh"

/* g_sprintf */
#include <glib.h>
#include <glib/gprintf.h>

#define MAX_TIME_BUF 42

namespace GManager
{
    Statusbar::Statusbar(Heartbeat& tproxy, MPD::Client& client, const Glib::RefPtr<Gtk::Builder>& builder) :
        AbstractClientUser(client)
    {
        BUILDER_GET(builder,"statusbar",m_Statusbar);

        mp_Message = NULL;
        mp_Lastdata = NULL;

        mp_Heartbeat = &tproxy;
        mp_Heartbeat->signal_client_update().connect(sigc::mem_fun(*this,&Statusbar::on_heartbeat));
    }

    /* ------------------ */

    Statusbar::~Statusbar(void)
    {
        g_free(mp_Message);
    }

    /* ------------------ */
    
    void Statusbar::on_connection_change(bool server_changed, bool is_connected)
    {
       if(is_connected == false)
          mp_Lastdata = NULL; 

        m_Statusbar->set_text("Not connected");
    }
    
    /* ------------------ */

    void Statusbar::format_time(unsigned time, char buffer[])
    {
        g_sprintf(buffer,"%d:%02d",time/60,time%60);
    }

    /* ------------------ */

    void Statusbar::on_client_update(enum mpd_idle event, MPD::NotifyData& data)
    {
        mp_Lastdata = &data;
        do_update_message(data);
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
