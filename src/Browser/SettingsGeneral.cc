#include "SettingsGeneral.hh"
#include "../Utils/Utils.hh"

namespace GManager
{
    SettingsGeneral::SettingsGeneral(const Glib::RefPtr<Gtk::Builder> &builder) :
        notify("signal"),
        tray("totray"),
        SettingsSub::name("General")
    {
        BUILDER_GET(builder,"libnotify_checkbox",libnotify);
        BUILDER_GET(builder,"trayicon_checkbox",trayicon);

    }


    SettingsGeneral::~SettingsGeneral(void) {}

    //----------------------------

    void SettingsGeneral::accept_new_settings(void)
    {
        int notify_value = (int) libnotify->get_active();
        int tray_value = (int) trayicon->get_active();

        CONFIG_SET_AS_INT(notify,notify_value);
        CONFIG_SET_AS_INT(tray,tray_value);
        Info(SettingsSub::get_name()+"Settings changed.");
    }

    //----------------------------

    void SettingsGeneral::decline_new_settings(void)
    {
        libnotify->set_active((bool)CONFIG_GET_AS_INT(notify));
        trayicon->set_active((bool)CONFIG_GET_AS_INT(tray));
        Info(SettingsSub::get_name()+"Settings reverted.");
    }

    //----------------------------

}
