#ifndef FREYA_TIMESLIDE_GUARD
#define FREYA_TIMESLIDE_GUARD

#include <gtkmm.h>
#include "Heartbeat.hh"
#include "AbstractGElement.hh"

namespace GManager
{
    class Timeslide : public AbstractGElement
    {
        public:
            Timeslide(Heartbeat& tproxy, MPD::Client& client, const Glib::RefPtr<Gtk::Builder>& builder);

        private:
            void tick(double time);
            void on_client_update(enum mpd_idle event, MPD::NotifyData& data);
            void on_connection_change(bool is_connected);
            void on_user_action(void);

            bool ignore_signal;
            Gtk::Scale * m_Timeslide;
            GManager::Heartbeat * mp_Proxy;

            Glib::Timer m_Timeguard;
    };
}
#endif
