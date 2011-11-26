#ifndef FREYA_SETTINGS_GENERAL_GUARD
#define FREYA_SETTINGS_GENERAL_GUARD

#include <gtkmm.h>

#include "../Config/Handler.hh"
#include "SettingsSub.hh"
#include "Settings.hh"

namespace Browser
{
    class SettingsGeneral : public SettingsSub
    {
        public:
            SettingsGeneral(const Glib::RefPtr<Gtk::Builder> &builder,Browser::Settings * sett);
            ~SettingsGeneral();

            void accept_new_settings(void);
            void decline_new_settings(void);
            void reset_settings(void);

        private:
            Glib::ustring notify,tray;
        /* Widgets */
            Gtk::CheckButton *libnotify, *trayicon;
    };
}
#endif
