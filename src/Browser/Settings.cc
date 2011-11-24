#include "Settings.hh"
#include "../Utils/Utils.hh"

#include "SettingsPlayback.hh"
#include "SettingsNetwork.hh"
#include "SettingsPlugins.hh"
#include "SettingsGeneral.hh"


#define SUBSECTION_COUNT 4;
#define PLUGIN_COUNT 4;
namespace Browser
{
    Settings:Settings(const Glib::RefPtr<Gtk::Builder> &builder):
        sub_sections(SUBSECTION_COUNT)
    {
        Glib::ustring settings_file("ui/Settings.glade");

        sub_sections.push_back(SettingsNetwork(builder));
        sub_sections.push_back(SettingsPlugins(builder,PLUGIN_COUNT));
        sub_sections.push_back(SettingsPlayback(builder));
        sub_sections.push_back(SettingsGeneral(builder));

        BUILDER_GET(builder,"ok_button",ok_button);
        BUILDER_GET(builder,"stop_button",stop_button);
        BUILDER_GET(builder,"settings_main",settings_main);

        ok_button->signal_clicked().connect(sigc::mem_fun(*this,&Settings::on_button_ok));
        stop_button->signal_clicked().connect(sigc::mem_fun(*this,&Settings::on_button_stop));



    }
    //---------------------------

    Settings::~Settings(void)
    {
    }

    //---------------------------

    void Settings::on_button_ok(void)
    {

        int rc=0;
        for(int i=0;i<SUBSECTION_COUNT;i++)
        {
            rc = sub_section[i]->validate();
            if(rc!=0)
            {
                Info("Couldn't validate "+sub_section[i]->get_name()+"-Settings. Please check input");
            }
        }
        for(int i=0;i<SUBSECTION_COUNT;i++)
        {
            sub_section[i]->accept_new_settings();
        }

    }
    //---------------------------
    void Settings::on_button_cancel(void)
    {
        for(int i=0;i<SUBSECTION_COUNT;i++)
        {
            sub_section[i]->decline_new_settings();
        }

    }
    //---------------------------
    Gtk::Widget* Settings::get_container(void)
    {
        return settings_main;
    }
    //---------------------------

}
