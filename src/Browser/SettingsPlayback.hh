#ifndef FREYA_SETTINGS_PLAYBACK_GUARD
#define FREYA_SETTINGS_PLAYBACK_GUARD

#include <gtkmm.h>

#include "../Config/Handler.hh"

namespace Browser
{
    class SettingsPlayback : SettingsSub
    {
        public:
            SettingsPlayback(const Glib::RefPtr<Gtk::Builder> &builder);
            ~SettingsPlayback();

            void accept_new_settings(void);
            void decline_new_settings(void);
            Glib::ustring get_name(void);
        private:
            Glib::ustring name, crossfade_name;
        /* Widgets */
            Gtk::SpinButton *crossfade;
    };
}
#endif
