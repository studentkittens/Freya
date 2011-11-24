#include "SettingsNetwork.hh"
#include "../Utils/Utils.hh"

namespace GManager
{
    SettingsNetwork::SettingsNetwork(const Glib::RefPtr<Gtk::Builder> &builder) :
        ip_name("host"),
        port_name("port"),
        timeout_name("reconnectintervall"),
        SettingsSub::name("Network")
    {
        BUILDER_GET(builder,"ip_textfield",ip);
        BUILDER_GET(builder,"port_spinbutton",port);
        BUILDER_GET(builder,"reconnect_spinbutton",recon_timeout);
    }


    SettingsNetwork::~SettingsNetwork(void) {}

    //----------------------------

    void SettingsNetwork::accept_new_settings(void)
    {

        Glib::ustring ip_value;
        int port_value, timeout_value;

        ip_value = ip->get_text();
        port_value = port->get_value_as_int();
        timeout_value = recon_timeout->get_value_as_int();

        CONFIG_SET(ip_name,ip_value);
        CONFIG_SET_AS_INT(port_name,port_value);
        CONFIG_SET_AS_INT(rimeout_name,timeout_value);
        Info(SettingsSub::get_name()+"Settings changed.");
    }

    //----------------------------

    void SettingsNetwork::decline_new_settings(void)
    {
        ip->set_text(CONFIG_GET(ip_name));
        port->set_value((double)CONFIG_GET_AS_INT(port_name));
        recon_timeout->set_value((double)CONFIG_GET_AS_INT(timeout_name));
        Info(SettingsSub::get_name()+"Settings reverted.");

    }

    //----------------------------

}
