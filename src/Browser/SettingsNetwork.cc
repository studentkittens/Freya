#include "SettingsNetwork.hh"
#include "../Utils/Utils.hh"

#include "../Avahi/Browser.hh"

namespace Browser
{
    SettingsNetwork::SettingsNetwork(const Glib::RefPtr<Gtk::Builder> &builder) :
        ip_name("settings.connection.host"),
        port_name("settings.connection.port"),
        timeout_name("settings.connection.reconnectintervall"),
        autoconnect_name("settings.connection.autoconnect"),
        SettingsSub::name("Network")
    {
        BUILDER_GET(builder,"ip_textfield",ip);
        BUILDER_GET(builder,"port_spinbutton",port);
        BUILDER_GET(builder,"reconnect_spinbutton",recon_timeout);
        BUILDER_GET(builder,"avahi_button",avahi);
        BUILDER_GET(builder,"autoconnect_checkbox",autoconnect);

        avahi->signal_clicked().connect(sigc:mem_fun(*this,show_avahi));
    }


    SettingsNetwork::~SettingsNetwork(void) {}

    //----------------------------

    void SettingsNetwork::accept_new_settings(void)
    {

        Glib::ustring ip_value;
        int port_value, timeout_value,autoconnect_value;

        ip_value = ip->get_text();
        port_value = port->get_value_as_int();
        timeout_value = recon_timeout->get_value_as_int();
        autoconnect_value =(int) autoconnect->get_active();
        CONFIG_SET(ip_name,ip_value);
        CONFIG_SET_AS_INT(port_name,port_value);
        CONFIG_SET_AS_INT(timeout_name,timeout_value);
        CONFIG_SET_AS_INT(autoconnect_name,autoconnect_value);
    }

    //----------------------------

    void SettingsNetwork::decline_new_settings(void)
    {
        ip->set_text(CONFIG_GET(ip_name));
        port->set_value((double)CONFIG_GET_AS_INT(port_name));
        recon_timeout->set_value((double)CONFIG_GET_AS_INT(timeout_name));
        autoconnect->set_value((double)CONFIG_GET_AS_INT(autoconnect_name));
    }

    //----------------------------
    void SettingsNetwork::show_avahi(void)
    {
        Avahi::Browser handle;
        if(handle.is_connected())
        {
            handle.get_signal().connect(sigc::ptr_fun(selected_callback));
            handle.get_window().show_all();
        }
    }
    //----------------------------

}
