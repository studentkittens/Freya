/***********************************************************
* This file is part of Freya
* - A free MPD Gtk3 MPD Client -
*
* Authors: Christopher Pahl, Christoph Piechula,
*          Eduard Schneider
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
#include "StatBrowser.hh"
#include "../../Utils/Utils.hh"
#include "../../Log/Writer.hh"

namespace Browser
{
    StatBrowser::StatBrowser(MPD::Client& client, Glib::RefPtr<Gtk::Builder>& builder) :
        AbstractBrowser("Statistics",true,true,Gtk::Stock::INFO)
    {
        Gtk::Grid * container = NULL;
        BUILDER_ADD(builder,"ui/Statistics.glade");
        BUILDER_GET(builder, "noofartist",noofartist);
        BUILDER_GET(builder, "noofalbums",noofalbums);
        BUILDER_GET(builder, "noofsongs",noofsongs);
        BUILDER_GET(builder, "dbplaytime",dbplaytime);
        BUILDER_GET(builder, "playtime",playtime);
        BUILDER_GET(builder, "uptime",uptime);
        BUILDER_GET(builder, "dbupdate",dbupdate);
        BUILDER_GET(builder, "statistics_grid",container);

        client.signal_client_update().connect(sigc::mem_fun(*this,&StatBrowser::on_client_update));
        container->reparent(*this);

        show_all();
    }


    StatBrowser::~StatBrowser()
    {
    }

    void StatBrowser::on_client_update(enum mpd_idle event, MPD::NotifyData& data)
    {
        int const BUFFER = 512;

        if (event & MPD_IDLE_DATABASE)
        {
            char newvalue[BUFFER] = {0};
            MPD::Statistics& stat = data.get_statistics();

            g_snprintf(newvalue,BUFFER,"%u artists",stat.get_number_of_artists());
            noofartist->set_text(Glib::ustring(newvalue));

            g_snprintf(newvalue,BUFFER,"%u albums",stat.get_number_of_albums());
            noofalbums->set_text(Glib::ustring(newvalue));

            g_snprintf(newvalue,BUFFER,"%u songs",stat.get_number_of_songs());
            noofsongs->set_text(Glib::ustring(newvalue));

            dbplaytime->set_text(Utils::seconds_to_duration(stat.get_db_play_time()).c_str());
            playtime->set_text(Utils::seconds_to_duration(stat.get_play_time()).c_str());
            uptime->set_text(Utils::seconds_to_duration(stat.get_uptime()).c_str());
            dbupdate->set_text(Utils::seconds_to_timestamp(stat.get_db_update_time()).c_str());
        }
    }


    Gtk::Widget * StatBrowser::get_container()
    {
        return this;
    }
}
