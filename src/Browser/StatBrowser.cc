#include "StatBrowser.hh"
#include "../Utils/Utils.hh"
#include "../Log/Writer.hh"

namespace Browser
{
    StatBrowser::StatBrowser(MPD::Client& client, Glib::RefPtr<Gtk::Builder>& builder) :
        AbstractBrowser("Statistics")
    {
        Gtk::Grid * container = NULL;
        BUILDER_ADD(builder,"ui/statistics.glade");
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
        if (event & MPD_IDLE_DATABASE)
        {
            MPD::Statistics& stat = data.get_statistics();
            char newvalue[] = {0};

            g_snprintf(newvalue,512,"%u",stat.get_number_of_artists());
            noofartist->set_text(Glib::ustring(newvalue));
            
            g_snprintf(newvalue,512,"%u",stat.get_number_of_albums());
            noofalbums->set_text(Glib::ustring(newvalue));
            
            g_snprintf(newvalue,512,"%u",stat.get_number_of_songs());
            noofsongs->set_text(Glib::ustring(newvalue));
            
            g_snprintf(newvalue,512,"%lu",stat.get_db_play_time());
            dbplaytime->set_text(Glib::ustring(newvalue));

            g_snprintf(newvalue,512,"%lu",stat.get_play_time());
            playtime->set_text(Glib::ustring(newvalue));


            g_snprintf(newvalue,512,"%lu",stat.get_uptime());
            uptime->set_text(Glib::ustring(newvalue));

            g_snprintf(newvalue,512,"%lu",stat.get_db_update_time());
            dbupdate->set_text(Glib::ustring(newvalue));

        }
    }


    Gtk::Widget * StatBrowser::get_container(void)
    {
        return this;
    }
}
