#ifndef FREYA_STATUSBAR_GUARD
#define FREYA_STATUSBAR_GUARD

#include <gtkmm.h>

#include "../MPD/Client.hh"
#include "Heartbeat.hh"

namespace GManager
{
    class Statusbar
    {
        public:

            Statusbar(Heartbeat& tproxy, MPD::Client& client, const Glib::RefPtr<Gtk::Builder>& builder);
            ~Statusbar();

        private:
            void on_client_update(enum mpd_idle, MPD::NotifyData& data);
            void on_heartbeat(double time);
            void format_time(unsigned time, char buffer[]);
            void do_update_message(MPD::NotifyData& data);

            MPD::NotifyData * mp_Lastdata;
            Gtk::Label * m_Statusbar;
            Heartbeat * mp_Proxy;
            gchar * mp_Message; 
    };
}
#endif
