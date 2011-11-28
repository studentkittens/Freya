#ifndef FREYA_SETTINGS_GENERAL_GUARD
#define FREYA_SETTINGS_GENERAL_GUARD

#include <gtkmm.h>

#include "../Config/Handler.hh"
#include "SettingsSub.hh"
#include "../GManager/Trayicon.hh"

namespace Browser
{
    class Settings;
    class SettingsGeneral : public SettingsSub
    {
        public:
            SettingsGeneral(const Glib::RefPtr<Gtk::Builder> &builder,Browser::Settings * sett, GManager::Trayicon *trayptr);
            ~SettingsGeneral();

            void accept_new_settings(void);
            void decline_new_settings(void);
            void reset_settings(void);

        private:
            void on_notify_toggled(void);
            void on_tray_toggled(void);
            GManager::Trayicon * trayptr;
            Browser::Settings * sett;
            Glib::ustring notify,tray,timeout, to_tray;
        /* Widgets */
            Gtk::CheckButton *libnotify, *trayicon, *close_to_tray;
            Gtk::SpinButton *notify_timeout;
            Gtk::Box *notify_box, *tray_box;
    };
}
#endif
