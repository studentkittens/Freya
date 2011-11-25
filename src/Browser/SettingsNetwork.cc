#include "SettingsNetwork.hh"
#include "../Utils/Utils.hh"
#include "../Log/Writer.hh"
#include "../AvahiBrowser/Browser.hh"

namespace Browser
{
    SettingsNetwork::SettingsNetwork(const Glib::RefPtr<Gtk::Builder> &builder) :
        ip_name("settings.connection.host"),
        port_name("settings.connection.port"),
        timeout_name("settings.connection.reconnectinterval"),
        autoconnect_name("settings.connection.autoconnect")
    {
        BUILDER_GET(builder,"ip_textfield",ip);
        BUILDER_GET(builder,"port_spinbutton",port);
        BUILDER_GET(builder,"reconnect_spinbutton",recon_timeout);
        BUILDER_GET(builder,"avahi_button",avahi);
        BUILDER_GET(builder,"autoconnect_checkbox",autoconnect);
        handle = NULL;
        avahi->signal_clicked().connect(sigc::mem_fun(*this,&Browser::SettingsNetwork::show_avahi));
    }


    SettingsNetwork::~SettingsNetwork(void)
    {
        if(handle!=NULL)
        {
            delete handle;
            handle=NULL;
        }
    }

    //----------------------------

    void SettingsNetwork::accept_new_settings(void)
    {

        Glib::ustring ip_value;
        int port_value, timeout_value;
        bool autoconnect_value;

        ip_value = ip->get_text();
        if(ip_value.size() == 0)
        {
            Info("Empty Server-IP entered. Falling back to previous IP");
                ip->set_text(CONFIG_GET(ip_name));
                ip_value = CONFIG_GET(ip_name);
        }
        port_value = port->get_value_as_int();
        timeout_value = recon_timeout->get_value_as_int();
        autoconnect_value = autoconnect->get_active();
        CONFIG_SET(ip_name,ip_value);
        CONFIG_SET_AS_INT(port_name,port_value);
        CONFIG_SET_AS_INT(timeout_name,timeout_value);
        CONFIG_SET_AS_INT(autoconnect_name,autoconnect_value?1:0);
    }

    //----------------------------

    void SettingsNetwork::decline_new_settings(void)
    {
        ip->set_text(CONFIG_GET(ip_name));
        port->set_value((double)CONFIG_GET_AS_INT(port_name));
        recon_timeout->set_value((double)CONFIG_GET_AS_INT(timeout_name));
        int autocon = CONFIG_GET_AS_INT(autoconnect_name);
        autoconnect->set_active(autocon==1?true:false);
    }

    //----------------------------
    void SettingsNetwork::show_avahi(void)
    {
        delete handle;
        handle = new Avahi::Browser();
        if(handle->is_connected())
        {
            handle->get_signal().connect(sigc::mem_fun(*this,&Browser::SettingsNetwork::selected_callback));
            handle->get_window().show();
        }

    }
    //----------------------------

    void SettingsNetwork::selected_callback(Glib::ustring ip,Glib::ustring hostname,Glib::ustring name, unsigned int port)
    {
        CONFIG_SET("settings.connection.host",ip);
        CONFIG_SET_AS_INT("settings.connection.port",port);
        this->ip->set_text(ip);
        this->port->set_value((double)port);
    }
}
