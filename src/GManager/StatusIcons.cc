#include "StatusIcons.hh"
#include "../Utils/Utils.hh"

namespace GManager
{

    Statusicons::Statusicons(MPD::Client& client, const Glib::RefPtr<Gtk::Builder>& builder)
    {
        ignore_updates = false;
        mp_Client = &client;
        mp_Client->get_notify().connect(sigc::mem_fun(*this,&Statusicons::on_client_update));

        BUILDER_GET(builder,"icon_random",mp_Random);
        mp_Random->signal_clicked().connect(sigc::mem_fun(*this,&Statusicons::on_clicked_random));

        BUILDER_GET(builder,"icon_single",mp_Single);
        mp_Single->signal_clicked().connect(sigc::mem_fun(*this,&Statusicons::on_clicked_single));

        BUILDER_GET(builder,"icon_repeat",mp_Repeat);
        mp_Repeat->signal_clicked().connect(sigc::mem_fun(*this,&Statusicons::on_clicked_repeat));

        BUILDER_GET(builder,"icon_consume",mp_Consume);
        mp_Consume->signal_clicked().connect(sigc::mem_fun(*this,&Statusicons::on_clicked_consume));

        BUILDER_GET(builder,"icon_conn",mp_Conn);
        mp_Conn->signal_clicked().connect(sigc::mem_fun(*this,&Statusicons::on_clicked_conn));

        mp_Client->signal_connection_change().connect(sigc::mem_fun(*this,&Statusicons::on_conn_change));
    }

    Statusicons::~Statusicons() { }

    void Statusicons::on_client_update(enum mpd_idle type, MPD::NotifyData& data)
    {
        if(type & (MPD_IDLE_OPTIONS))
        {
            ignore_updates = true;
            MPD::Status& status = data.get_status();
            mp_Consume->set_active(status.get_consume()); 
            mp_Random->set_active(status.get_random()); 
            mp_Repeat->set_active(status.get_repeat()); 
            mp_Single->set_active(status.get_single()); 
            ignore_updates = false;
        }
    }

    void Statusicons::on_clicked_random(void)
    {
        if(!ignore_updates) mp_Client->toggle_random(); 
    }

    void Statusicons::on_clicked_single(void)
    {
        if(!ignore_updates) mp_Client->toggle_single(); 
    }

    void Statusicons::on_clicked_consume(void)
    {
        if(!ignore_updates) mp_Client->toggle_consume(); 
    }

    void Statusicons::on_clicked_repeat(void)
    {
        if(!ignore_updates) mp_Client->toggle_repeat(); 
    }

    void Statusicons::on_clicked_conn(void)
    {
        if(mp_Client->is_connected())
        {
            mp_Client->disconnect();
            g_printerr("Disconnecting.");
        }
        else
        {
            mp_Client->connect();
            g_printerr("Conn.");
        }
    }

    void Statusicons::on_conn_change(bool is_connected)
    {
        g_printerr("Sens\n");
    }
}
