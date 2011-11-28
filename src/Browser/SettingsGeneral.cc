#include "SettingsGeneral.hh"
#include "../Utils/Utils.hh"
#include "Settings.hh"
namespace Browser
{
    SettingsGeneral::SettingsGeneral(const Glib::RefPtr<Gtk::Builder> &builder,Browser::Settings * sett) :
        notify("settings.libnotify.signal"),
        tray("settings.trayicon.totray"),
        timeout("settings.libnotify.timeout")
    {
        BUILDER_GET(builder,"libnotify_checkbox",libnotify);
        BUILDER_GET(builder,"trayicon_checkbox",trayicon);
        BUILDER_GET(builder,"notification_timeout",notify_timeout);
        BUILDER_GET(builder,"notify_box",notify_box);

        libnotify->signal_toggled().connect(sigc::mem_fun(*sett,&Browser::Settings::settings_changed));
        libnotify->signal_toggled().connect(sigc::mem_fun(*this,&Browser::SettingsGeneral::on_notify_toggled));
        notify_timeout->signal_changed().connect(sigc::mem_fun(*sett,&Browser::Settings::settings_changed));

        on_notify_toggled();

        trayicon->signal_toggled().connect(sigc::mem_fun(*sett,&Browser::Settings::settings_changed));
    }


    SettingsGeneral::~SettingsGeneral(void) {}

    //----------------------------

    void SettingsGeneral::accept_new_settings(void)
    {
        bool notify_value =  libnotify->get_active();
        bool tray_value =  trayicon->get_active();
        int timeout_value =(int)notify_timeout->get_value();
        CONFIG_SET_AS_INT(notify,notify_value?1:0);
        CONFIG_SET_AS_INT(tray,tray_value?1:0);
        CONFIG_SET_AS_INT(timeout,timeout_value?timeout_value*1000:-1);
    }

    //----------------------------

    void SettingsGeneral::decline_new_settings(void)
    {
        int libnot, trayic, timeout_value;
        libnot = CONFIG_GET_AS_INT(notify);
        trayic = CONFIG_GET_AS_INT(tray);
        timeout_value = CONFIG_GET_AS_INT(timeout);
        notify_timeout->set_value((double)(timeout_value==-1?0:((double)timeout_value)/1000) );
        libnotify->set_active(libnot==1);
        trayicon->set_active(trayic==1);
    }

    //----------------------------

    void SettingsGeneral::reset_settings(void)
    {
        int libnot, trayic, timeout_value;
        libnot = CONFIG_GET_DEFAULT_AS_INT(notify);
        trayic = CONFIG_GET_DEFAULT_AS_INT(tray);
        timeout_value = CONFIG_GET_DEFAULT_AS_INT(timeout);
        libnotify->set_active(libnot==1);
        trayicon->set_active(trayic==1);
        notify_timeout->set_value((double)(timeout_value==-1?0:((double)timeout_value)/1000) );
    }

    //----------------------------

    void SettingsGeneral::on_notify_toggled(void)
    {
        notify_box->set_visible(libnotify->get_active());
    }
}
