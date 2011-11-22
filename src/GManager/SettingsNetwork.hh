#ifndef FREYA_SETTINGS_PLUGINS_GUARD
#define FREYA_SETTINGS_PLUGINS_GUARD

#include <gtkmm.h>

#include "../Config/Handler.hh"

namespace GManager
{
    class SettingsPlugins : SettingsSub
    {
        public:
            SettingsPlugins(const Glib::RefPtr<Gtk::Builder> &builder);
            ~SettingsPlugins();

            void accept_new_settings(void);
            void decline_new_settings(void);

        private:
        /* Widgets */
            Gtk::Entry *ip;
            Gtk::SpinButton *port, *recon_timeout;
    };
}
#endif
