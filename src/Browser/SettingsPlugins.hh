#ifndef FREYA_SETTINGS_PLUGINS_GUARD
#define FREYA_SETTINGS_PLUGINS_GUARD

#include <gtkmm.h>

#include "../Config/Handler.hh"

#include <vector>
using namespace std;
namespace Browser
{

    class SettingsPlugins : public SettingsSub
    {
        public:
            SettingsPlugins(const Glib::RefPtr<Gtk::Builder> &builder, 
            int _plugin_count);
            ~SettingsPlugins();

            void accept_new_settings(void);
            void decline_new_settings(void);

        private:
            int plugin_count;
            Glib::ustring port_name;
        /* Widgets */
            vector<Gtk::CheckButton*> plugin_check_box;

    };

}
#endif
