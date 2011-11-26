#ifndef FREYA_STATUSICONS_GUARD
#define FREYA_STATUSICONS_GUARD

#include <gtkmm.h>
#include "../MPD/Client.hh"

namespace GManager
{
    class Statusicons
    {
        public:

            Statusicons(MPD::Client& client, const Glib::RefPtr<Gtk::Builder>& builder);
            ~Statusicons();

        private:

            void on_client_update(enum mpd_idle, MPD::NotifyData& data);
            void on_clicked_random(void);
            void on_clicked_single(void);
            void on_clicked_consume(void);
            void on_clicked_repeat(void);
            void on_conn_change(bool is_connected);

            /* Widgets */
            Gtk::ToggleButton *mp_Random, * mp_Single, * mp_Consume, * mp_Repeat;
            MPD::Client * mp_Client;

            /* set_active() emits a signal, this would cause infinite loops of updating,
             * ignore signals while recv. updates from client therefore. */
            bool ignore_updates;
    };
}

#endif
