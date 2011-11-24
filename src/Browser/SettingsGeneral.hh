#ifndef FREYA_SETTINGS_GENERAL_GUARD
#define FREYA_SETTINGS_GENERAL_GUARD

#include <gtkmm.h>

#include "../Config/Handler.hh"

namespace Browser
{
    class SettingsGeneral : SettingsSub
    {
        public:
            SettingsGeneral(const Glib::RefPtr<Gtk::Builder> &builder);
            ~SettingsGeneral();

            void accept_new_settings(void);
            void decline_new_settings(void);

        private:
            Glib::ustring notify,tray;
        /* Widgets */
            Gtk::CheckButton *libnotify, *trayicon;
    };
}
#endif
