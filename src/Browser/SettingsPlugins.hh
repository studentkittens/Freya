#ifndef FREYA_SETTINGS_PLUGINS_GUARD
#define FREYA_SETTINGS_PLUGINS_GUARD

#include <gtkmm.h>

#include "../Config/Handler.hh"

#include <vector>
namespace Browser
{

    class SettingsPlugins : SettingsSub
    {
        public:
            SettingsPlugins(const Glib::RefPtr<Gtk::Builder> &builder, char _plugin_count);
            ~SettingsPlugins();

            void accept_new_settings(void);
            void decline_new_settings(void);

        private:
            char plugin_count;
        /* Widgets */
            vector<Gtk::CheckButton*> plugin_check_box;

    };

}
#endif
