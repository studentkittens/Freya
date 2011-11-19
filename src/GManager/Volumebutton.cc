#include "Volumebutton.hh"
#include "../Utils/Utils.hh"

#define UPDATE_TIMEOUT 0.05

namespace GManager
{
    Volumebutton::Volumebutton(MPD::Client& client, const Glib::RefPtr<Gtk::Builder>& builder) :
        m_Timerguard()
    {
        ignore_signal = false;

        BUILDER_GET(builder,"volume_button",mp_VButton);
        mp_VButton->signal_value_changed().connect(sigc::mem_fun(*this,&GManager::Volumebutton::on_user_change));

        client.get_notify().connect(sigc::mem_fun(*this,&Volumebutton::on_client_updates));
        mp_Client = &client;
    }

    // -------------------

    Volumebutton::~Volumebutton(void) {}

    // -------------------

    void Volumebutton::on_client_updates(enum mpd_idle event, MPD::NotifyData& data)
    {
        if(event & (MPD_IDLE_MIXER))
        {
            /* Make sure the signal emitted by set_value() is ignored */
            ignore_signal = true;
            mp_VButton->set_value(data.get_status().get_volume() / 100.0);
            ignore_signal = false;
        }
    }

    // -------------------
    
    void Volumebutton::on_user_change(double val)
    {
        if(!ignore_signal && m_Timerguard.elapsed() > UPDATE_TIMEOUT) 
        {
            mp_Client->set_volume(mp_VButton->get_value() * 100);
            m_Timerguard.reset();
        }
    }
}
