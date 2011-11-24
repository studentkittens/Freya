#include "SettingsPlugins.hh"
#include "../Utils/Utils.hh"

namespace GManager
{
    SettingsPlugins::SettingsPlugins(const Glib::RefPtr<Gtk::Builder> &builder, int _plugin_count) :
        plugin_count(_plugin_count),
        SettingsSub::name("Plugins")
    {
        plugin_check_box = new Gtk::CheckButton[plugin_count];

        for(int i=0;i<plugin_count;i++)
        {
            BUILDER_GET(builder,"plugin"+i+1,plugin_check_box[i]);
        }
    }


    SettingsPlugins::~SettingsPlugins(void)
    {
        if(plugin_check_box!=NULL)
        {
            delete[] plugin_check_box;
            plugin_check_box=NULL;
        }
    }

    //----------------------------

    void SettingsPlugins::accept_new_settings(void)
    {

        CONFIG_SET(ip_name,ip_value);
        CONFIG_SET_AS_INT(port_name,port_value);
        CONFIG_SET_AS_INT(rimeout_name,timeout_value);
        Info(SettingsSub::get_name()+"Settings changed.");
    }

    //----------------------------

    void SettingsPlugins::decline_new_settings(void)
    {
        ip->set_text(CONFIG_GET(ip_name));
        Info(SettingsSub::get_name()+"Settings reverted.");

    }

    //----------------------------


}
