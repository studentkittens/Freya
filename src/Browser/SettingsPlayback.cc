#include "SettingsPlayback.hh"
#include "../Utils/Utils.hh"

namespace Browser
{
    SettingsPlayback::SettingsPlayback(const Glib::RefPtr<Gtk::Builder> &builder) :
        crossfade_name("settings.playback.crossfade"),
        stoponexit_name("settings.playback.stoponexit")
    {
        BUILDER_GET(builder,"crossfade_spinbutton",crossfade);
        BUILDER_GET(builder,"stoponexit_checkbox",stoponexit);
    }


    SettingsPlayback::~SettingsPlayback(void) {}

    //----------------------------

    void SettingsPlayback::accept_new_settings(void)
    {
        int crossfade_value = (int) crossfade->get_value_as_int();
        bool stoponexit_value =  stoponexit->get_active();

        CONFIG_SET_AS_INT(crossfade_name,crossfade_value);
        CONFIG_SET_AS_INT(stoponexit_name,stoponexit_value?1:0);
    }

    //----------------------------

    void SettingsPlayback::decline_new_settings(void)
    {
        crossfade->set_value(CONFIG_GET_AS_INT(crossfade_name));
        stoponexit->set_active(CONFIG_GET_AS_INT(stoponexit_name)==1);
    }

    //----------------------------

    void SettingsPlayback::reset_settings(void)
    {
        crossfade->set_value(CONFIG_GET_DEFAULT_AS_INT(crossfade_name));
        stoponexit->set_active(CONFIG_GET_DEFAULT_AS_INT(stoponexit_name)==1);
    }
}
