#include "Volumebutton.hh"
#include "../Utils/Utils.hh"

namespace GManager
{
    Volumebutton::Volumebutton(MPD::Client& client, const Glib::RefPtr<Gtk::Builder>& builder)
    {
        ignore_signal = false;

        BUILDER_GET(builder,"volume_button",mp_VButton);
        mp_VButton->signal_value_changed().connect(sigc::mem_fun(*this,&GManager::Volumebutton::on_user_change));

        client.get_notify().connect(sigc::mem_fun(*this,&Volumebutton::on_client_updates));
        mp_Client = &client;
    }

    Volumebutton::~Volumebutton(void) {}


    void Volumebutton::on_client_updates(enum mpd_idle event, MPD::NotifyData& data)
    {
        if(event & MPD_IDLE_MIXER)
        {
            ignore_signal = true;
        g_printerr("<- %d\n",data.get_status().get_volume());
            mp_VButton->set_value(data.get_status().get_volume() / 100.0);
            ignore_signal = false;
        }
    }

    void Volumebutton::on_user_change(double val)
    {
        g_printerr("-> %f\n",mp_VButton->get_value());
        if(!ignore_signal) mp_Client->set_volume(mp_VButton->get_value() * 100);
    }
}
