#include "SettingsPlayback.hh"
#include "../Utils/Utils.hh"

namespace Browser
{
    SettingsPlayback::SettingsPlayback(const Glib::RefPtr<Gtk::Builder> &builder) :
        crossfade_name("settings.playback.crossfade")
    {
        BUILDER_GET(builder,"crossfade_spinbutton",crossfade);
    }


    SettingsPlayback::~SettingsPlayback(void) {}

    //----------------------------

    void SettingsPlayback::accept_new_settings(void)
    {
        int crossfade_value = (int) crossfade->get_value_as_int();

        CONFIG_SET_AS_INT(crossfade_name,crossfade_value);
    }

    //----------------------------

    void SettingsPlayback::decline_new_settings(void)
    {
        crossfade->set_value(CONFIG_GET_AS_INT(crossfade_name));
    }

    //----------------------------

}
