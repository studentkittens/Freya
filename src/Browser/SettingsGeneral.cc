#include "SettingsGeneral.hh"
#include "../Utils/Utils.hh"

namespace Browser
{
    SettingsGeneral::SettingsGeneral(const Glib::RefPtr<Gtk::Builder> &builder) :
        notify("settings.libnotify.signal"),
        tray("settings.trayicon.totray")
    {
        BUILDER_GET(builder,"libnotify_checkbox",libnotify);
        BUILDER_GET(builder,"trayicon_checkbox",trayicon);

    }


    SettingsGeneral::~SettingsGeneral(void) {}

    //----------------------------

    void SettingsGeneral::accept_new_settings(void)
    {
        bool notify_value =  libnotify->get_active();
        bool tray_value =  trayicon->get_active();

        CONFIG_SET_AS_INT(notify,notify_value?1:0);
        CONFIG_SET_AS_INT(tray,tray_value?1:0);
    }

    //----------------------------

    void SettingsGeneral::decline_new_settings(void)
    {
        int libnot, trayic;
        libnot = CONFIG_GET_AS_INT(notify);
        trayic = CONFIG_GET_AS_INT(tray);
        libnotify->set_active(libnot==1);
        trayicon->set_active(trayic==1);
    }

    //----------------------------

    void SettingsGeneral::reset_settings(void)
    {
        int libnot, trayic;
        libnot = CONFIG_GET_DEFAULT_AS_INT(notify);
        trayic = CONFIG_GET_DEFAULT_AS_INT(tray);
        libnotify->set_active(libnot==1);
        trayicon->set_active(trayic==1);
    }
}
