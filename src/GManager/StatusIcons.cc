#include "StatusIcons.hh"
#include "../Utils/Utils.hh"

namespace GManager
{

    Statusicons::Statusicons(MPD::Client& client, const Glib::RefPtr<Gtk::Builder>& builder)
    {
        try
        {
            mp_Client = &client;
            mp_Client->get_notify().connect(sigc::mem_fun(*this,&Statusicons::on_client_update));

            BUILDER_GET(builder,"icon_random",mp_Random);
            mp_Random->signal_clicked().connect(sigc::mem_fun(*this,&Statusicons::on_clicked_random));

            BUILDER_GET(builder,"icon_single",mp_Single);
            mp_Random->signal_clicked().connect(sigc::mem_fun(*this,&Statusicons::on_clicked_single));

            BUILDER_GET(builder,"icon_repeat",mp_Repeat);
            mp_Random->signal_clicked().connect(sigc::mem_fun(*this,&Statusicons::on_clicked_repeat));

            BUILDER_GET(builder,"icon_consume",mp_Consume);
            mp_Random->signal_clicked().connect(sigc::mem_fun(*this,&Statusicons::on_clicked_consume));
        }
        catch(const Gtk::BuilderError& e)
        {
            Error("BuilderError: %s",e.what().c_str());
        }
    }

    Statusicons::~Statusicons() { }

    void Statusicons::on_client_update(enum mpd_idle, MPD::NotifyData& data)
    {
        MPD::Status& status = data.get_status();
        mp_Consume->set_active(status.get_consume()); 
        mp_Random->set_active(status.get_random()); 
        mp_Repeat->set_active(status.get_repeat()); 
        mp_Single->set_active(status.get_single()); 
    }

    void Statusicons::on_clicked_random(void)
    {
       Debug("Toggle random");
       mp_Client->toggle_random(); 
    }

    void Statusicons::on_clicked_single(void)
    {
       mp_Client->toggle_single(); 
    }

    void Statusicons::on_clicked_consume(void)
    {
       mp_Client->toggle_consume(); 
    }

    void Statusicons::on_clicked_repeat(void)
    {
       mp_Client->toggle_repeat(); 
    }
}
