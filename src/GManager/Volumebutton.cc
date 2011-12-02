#include "Volumebutton.hh"
#include "../Utils/Utils.hh"
#include "../Notify/Notify.hh"

#define UPDATE_TIMEOUT 0.1//seconds

namespace GManager
{
    Volumebutton::Volumebutton(MPD::Client& client, const Glib::RefPtr<Gtk::Builder>& builder) :
        AbstractClientUser(client),
        m_Timerguard()
    {
        ignore_signal = false;
        BUILDER_GET(builder,"volume_button",mp_VButton);
        mp_VButton->signal_value_changed().connect(sigc::mem_fun(*this,&GManager::Volumebutton::on_user_change));
    }

    // -------------------

    void Volumebutton::on_client_update(enum mpd_idle event, MPD::NotifyData& data)
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
    
    void Volumebutton::on_connection_change(bool is_connected)
    {
        // TODO
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
