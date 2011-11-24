#ifndef FREYA_SETTINGS_NETWORK_GUARD
#define FREYA_SETTINGS_NETWORK_GUARD

#include <gtkmm.h>

#include "../Config/Handler.hh"
#include "SettingsSub.hh"
namespace Browser
{
    class SettingsNetwork : public  SettingsSub
    {
        public:
            SettingsNetwork(const Glib::RefPtr<Gtk::Builder> &builder);
            ~SettingsNetwork();

            void accept_new_settings(void);
            void decline_new_settings(void);

        private:
            void show_avahi(void);
            Glib::ustring ip_name, port_name, timeout_name, autoconnect_name;
        /* Widgets */
            Gtk::Entry *ip;
            Gtk::SpinButton *port, *recon_timeout;
            Gtk::Button *avahi;
            Gtk::CheckButton *autoconnect;
    };
}
#endif