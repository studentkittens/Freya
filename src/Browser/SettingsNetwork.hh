#ifndef FREYA_SETTINGS_NETWORK_GUARD
#define FREYA_SETTINGS_NETWORK_GUARD

#include <gtkmm.h>

#include "../Config/Handler.hh"
#include "SettingsSub.hh"
#include "../AvahiBrowser/Browser.hh"
#include "Settings.hh"

namespace Browser
{
    class SettingsNetwork : public  SettingsSub
    {
        public:
            SettingsNetwork(const Glib::RefPtr<Gtk::Builder> &builder,Browser::Settings * sett);
            ~SettingsNetwork();

            void accept_new_settings(void);
            void decline_new_settings(void);
            void reset_settings(void);

        private:
            void show_avahi(void);
            void selected_callback(Glib::ustring ip,Glib::ustring hostname,Glib::ustring name, unsigned int port);
            Glib::ustring ip_name, port_name, timeout_name, autoconnect_name;
        /* Widgets */
            Avahi::Browser* handle;
            Gtk::Entry *ip;
            Gtk::SpinButton *port, *recon_timeout;
            Gtk::Button *avahi;
            Gtk::CheckButton *autoconnect;
            Gtk::MessageDialog *avahi_warning;
    };
}
#endif
