#ifndef FREYA_VOLUMEBUTTON_GUARD
#define FREYA_VOLUMEBUTTON_GUARD

#include <gtkmm.h>
#include <gtkmm/volumebutton.h>
#include "../MPD/Client.hh"

namespace GManager
{
    class Volumebutton
    {
        public:
            Volumebutton(MPD::Client& client, const Glib::RefPtr<Gtk::Builder>& builder);
            ~Volumebutton(void);

        private:

            void on_client_updates(enum mpd_idle type, MPD::NotifyData& data);
            void on_user_change(double val);

            bool ignore_signal;
            MPD::Client * mp_Client;
            Gtk::VolumeButton * mp_VButton;
    };
}

#endif
