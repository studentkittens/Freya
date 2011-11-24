#ifndef FREYA_SETTINGS_GUARD
#define FREYA_SETTINGS_GUARD

#include <gtkmm.h>

#include "../Config/Handler.hh"
#include <vector>
namespace Browser
{
    class Settings
    {
        public:
            Settings(const Glib::RefPtr<Gtk::Builder> &builder>);
            ~Settings();
        private:
            void on_button_ok(void);
            void on_button_cancel(void);

            vector<SettingsSub> sub_sections;

            /* Widgets */
            Gtk::Button *ok_button, *cancel_button;
    };
}

#endif
