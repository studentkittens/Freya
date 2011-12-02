#include "StatBrowser.hh"
#include "../Utils/Utils.hh"
#include "../Log/Writer.hh"

namespace Browser
{
    StatBrowser::StatBrowser(MPD::Client& client, Glib::RefPtr<Gtk::Builder>& builder) :
        AbstractBrowser("Statistics",Gtk::Stock::INFO)
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

        client.get_notify().connect(sigc::mem_fun(*this,&StatBrowser::on_client_update));
        container->reparent(*this);

        show_all();
    }


    StatBrowser::~StatBrowser()
    {
    }

    void StatBrowser::on_client_update(enum mpd_idle event, MPD::NotifyData& data)
    {
        int const buffer = 512;

        if (event & MPD_IDLE_DATABASE)
        {
            char newvalue[buffer] = {0};
            MPD::Statistics& stat = data.get_statistics();
            
            g_snprintf(newvalue,buffer,"%u artists",stat.get_number_of_artists());
            noofartist->set_text(Glib::ustring(newvalue));

            g_snprintf(newvalue,buffer,"%u albums",stat.get_number_of_albums());
            noofalbums->set_text(Glib::ustring(newvalue));

            g_snprintf(newvalue,buffer,"%u songs",stat.get_number_of_songs());
            noofsongs->set_text(Glib::ustring(newvalue));

            dbplaytime->set_text(Utils::seconds_to_duration(stat.get_db_play_time()).c_str());

            playtime->set_text(Utils::seconds_to_duration(stat.get_play_time()).c_str());

            uptime->set_text(Utils::seconds_to_duration(stat.get_uptime()).c_str());

            dbupdate->set_text(Utils::seconds_to_timestamp(stat.get_db_update_time()).c_str());
        
        }
    }


    Gtk::Widget * StatBrowser::get_container(void)
    {
        return this;
    }
}
