#ifndef FREYA_SETTINGS_PLAYBACK_GUARD
#define FREYA_SETTINGS_PLAYBACK_GUARD

#include <gtkmm.h>

#include "../Config/Handler.hh"
#include "SettingsSub.hh"
#include "Settings.hh"
namespace Browser
{
    class SettingsPlayback : public SettingsSub
    {
        public:
            SettingsPlayback(const Glib::RefPtr<Gtk::Builder> &builder,Browser::Settings * sett);
            ~SettingsPlayback();

            void accept_new_settings(void);
            void decline_new_settings(void);
            void reset_settings(void);
        private:
            Glib::ustring name, crossfade_name, stoponexit_name;
        /* Widgets */
            Gtk::SpinButton *crossfade;
            Gtk::CheckButton *stoponexit;
    };
}
#endif
