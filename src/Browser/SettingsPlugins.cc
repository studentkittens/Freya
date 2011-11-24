#include "SettingsPlugins.hh"
#include "../Utils/Utils.hh"

namespace Browser
{
    SettingsPlugins::SettingsPlugins(const Glib::RefPtr<Gtk::Builder> &builder, int _plugin_count) :
        plugin_count(_plugin_count),
        plugin_check_box(_plugin_count)
    {
        for(int i=0;i<plugin_count;i++)
        {
            BUILDER_GET(builder,"plugin"+i+1,plugin_check_box[i]);
        }
    }


    SettingsPlugins::~SettingsPlugins(void)
    {
    }

    //----------------------------

    void SettingsPlugins::accept_new_settings(void)
    {

        CONFIG_SET_AS_INT(port_name,port_value);
    }

    //----------------------------

    void SettingsPlugins::decline_new_settings(void)
    {
        plugin_check_box.set_active(CONFIG_GET());

    }

    //----------------------------


}
