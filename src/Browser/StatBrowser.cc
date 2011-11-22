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
        BUILDER_GET(builder, "noofartist",playtime);
        BUILDER_GET(builder, "noofalbums",playtime);
        BUILDER_GET(builder, "noofsongs",playtime);
        BUILDER_GET(builder, "dbplaytime",playtime);
        BUILDER_GET(builder, "playtime",playtime);
        BUILDER_GET(builder, "uptime",playtime);
        BUILDER_GET(builder, "dbupdate",playtime);
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
            char* newplaytime = (char*)g_strdup_printf("%lu",stat.get_play_time());
            playtime->set_text(Glib::ustring(newplaytime));
            g_free(newplaytime);              

        }
    }

    Gtk::Widget * StatBrowser::get_container(void)
    {
        return this;
    }
}
