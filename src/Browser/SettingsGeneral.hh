#ifndef FREYA_SETTINGS_GENERAL_GUARD
#define FREYA_SETTINGS_GENERAL_GUARD

#include <gtkmm.h>

#include "../Config/Handler.hh"
#include "SettingsSub.hh"

namespace Browser
{
    class Settings;
    class SettingsGeneral : public SettingsSub
    {
        public:
            SettingsGeneral(const Glib::RefPtr<Gtk::Builder> &builder,Browser::Settings * sett);
            ~SettingsGeneral();

            void accept_new_settings(void);
            void decline_new_settings(void);
            void reset_settings(void);

        private:
            void on_notify_toggled(void);
            Glib::ustring notify,tray,timeout;
        /* Widgets */
            Gtk::CheckButton *libnotify, *trayicon;
            Gtk::SpinButton *notify_timeout;
            Gtk::Box *notify_box;
    };
}
#endif
