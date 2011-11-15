#include "StatusIcons.hh"

namespace GManager
{

    Statusicons::Statusicons(MPD::Client& client, const Glib::RefPtr<Gtk::Builder>& builder)
    {
        try
        {
            mp_Client = &client;
            mp_Client->get_notify().connect(sigc::mem_fun(*this,&Statusicons::on_client_update));

            Debug("Huh?!");

            builder->get_widget("icon_random",mp_Random);
            mp_Random->signal_clicked().connect(sigc::mem_fun(*this,&Statusicons::on_clicked_random));
            Gtk::manage(mp_Random);

            builder->get_widget("icon_single",mp_Single);
            mp_Random->signal_clicked().connect(sigc::mem_fun(*this,&Statusicons::on_clicked_single));
            Gtk::manage(mp_Random);

            builder->get_widget("icon_repeat",mp_Repeat);
            mp_Random->signal_clicked().connect(sigc::mem_fun(*this,&Statusicons::on_clicked_repeat));
            Gtk::manage(mp_Random);

            builder->get_widget("icon_consume",mp_Consume);
            mp_Random->signal_clicked().connect(sigc::mem_fun(*this,&Statusicons::on_clicked_consume));
            Gtk::manage(mp_Random);
        }
        catch(const Gtk::BuilderError& e)
        {
            Error("BuilderError: %s",e.what().c_str());
        }
    }

    Statusicons::~Statusicons()
    {
        
    }

    void Statusicons::on_client_update(enum mpd_idle, MPD::NotifyData& data)
    {
        // TODO
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
