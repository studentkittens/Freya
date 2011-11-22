#ifndef FREYA_SETTINGS_NETWORK_GUARD
#define FREYA_SETTINGS_NETWORK_GUARD

#include <gtkmm.h>

#include "../Config/Handler.hh"

namespace GManager
{
    class SettingsNetwork : SettingsSub
    {
        public:
            SettingsNetwork(const Glib::RefPtr<Gtk::Builder> &builder);
            ~SettingsNetwork();

            void accept_new_settings(void);
            void decline_new_settings(void);

        private:
            Glib::ustring ip_name, port_name, timeout_name;
        /* Widgets */
            Gtk::Entry *ip;
            Gtk::SpinButton *port, *recon_timeout;
    };
}
#endif
