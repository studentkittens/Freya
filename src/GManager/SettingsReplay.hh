#ifndef FREYA_SETTINGS_REPLAY_GUARD
#define FREYA_SETTINGS_REPLAY_GUARD

#include <gtkmm.h>

#include "../Config/Handler.hh"

namespace GManager
{
    class SettingsReplay : SettingsSub
    {
        public:
            SettingsReplay(const Glib::RefPtr<Gtk::Builder> &builder);
            ~SettingsReplay();

            void accept_new_settings(void);
            void decline_new_settings(void);

        private:
        /* Widgets */
            Gtk::SpinButton *crossfade;
    };
}
#endif
