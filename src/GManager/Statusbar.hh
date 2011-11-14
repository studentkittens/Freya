#ifndef FREYA_STATUSBAR_GUARD
#define FREYA_STATUSBAR_GUARD

#include <gtkmm.h>

#include "../MPD/Client.hh"

namespace GManager
{
    class Statusbar
    {
        public:

            Statusbar(MPD::Client& client, const Glib::RefPtr<Gtk::Builder>& builder);
            ~Statusbar();

        private:
            void on_client_update(enum mpd_idle, MPD::NotifyData& data);
            void format_time(unsigned time, char buffer[]);

            MPD::NotifyData * mp_Lastdata;
            Gtk::Statusbar * m_Statusbar;
            gchar * mp_Message; 
    };
}
#endif
