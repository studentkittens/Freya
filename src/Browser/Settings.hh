#ifndef FREYA_SETTINGS_GUARD
#define FREYA_SETTINGS_GUARD

#include <gtkmm.h>

#include "../Config/Handler.hh"
#include <vector>
#include "SettingsPlayback.hh"
#include "SettingsNetwork.hh"
#include "SettingsGeneral.hh"
#include "SettingsSub.hh"
#include "../AbstractBrowser.hh"
using namespace std;

namespace Browser
{
    class Settings : public AbstractBrowser
    {
        public:
            Settings(const Glib::RefPtr<Gtk::Builder> &builder);
            ~Settings();
            Gtk::Widget* get_container(void);
        private:
            void on_button_ok(void);
            void on_button_cancel(void);
            void on_button_reset(void);

            vector<SettingsSub*> sub_sections;
            /* Widgets */
            Gtk::Button *ok_button, *cancel_button, *reset_button;
            Gtk::Box *settings_main;

    };
}

#endif
