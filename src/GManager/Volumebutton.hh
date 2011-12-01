#ifndef FREYA_VOLUMEBUTTON_GUARD
#define FREYA_VOLUMEBUTTON_GUARD

#include <gtkmm.h>
#include <gtkmm/volumebutton.h>
#include "../MPD/Client.hh"
#include "AbstractGElement.hh"

namespace GManager
{
    class Volumebutton : public AbstractGElement
    {
        public:
            Volumebutton(MPD::Client& client, const Glib::RefPtr<Gtk::Builder>& builder);

        private:

            void on_client_update(enum mpd_idle type, MPD::NotifyData& data);
            void on_connection_change(bool is_connected);
            void on_user_change(double val);
            void volume_notify(int curVol);

            bool ignore_signal;
            Gtk::VolumeButton * mp_VButton;
            Glib::Timer m_Timerguard;
    };
}

#endif
