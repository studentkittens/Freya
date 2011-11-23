#ifndef FREYA_TIMESLIDE_GUARD
#define FREYA_TIMESLIDE_GUARD

#include <gtkmm.h>
#include "Heartbeat.hh"

namespace GManager
{
    class Timeslide 
    {
        public:

            Timeslide(Heartbeat& tproxy, MPD::Client& client, const Glib::RefPtr<Gtk::Builder>& builder);
            ~Timeslide();

        private:

            void tick(double time);
            void on_client_update(enum mpd_idle event, MPD::NotifyData& data);
            void on_user_action(void);

            bool ignore_signal;
            Gtk::Scale * m_Timeslide;
            MPD::Client * mp_Client;
            GManager::Heartbeat * mp_Proxy;

            Glib::Timer m_Timeguard;
    };
}
#endif
