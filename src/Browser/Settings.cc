#include "Settings.hh"
#include "../Utils/Utils.hh"
#include "../Log/Writer.hh"

#define PLUGIN_COUNT 4
namespace Browser
{
    Settings::Settings(const Glib::RefPtr<Gtk::Builder> &builder):
        AbstractBrowser("Settings",Gtk::Stock::PREFERENCES)
    {
        BUILDER_ADD(builder,"ui/Settings.glade");
        BUILDER_GET(builder,"ok_button",ok_button);
        BUILDER_GET(builder,"cancel_button",cancel_button);
        BUILDER_GET(builder,"settings_main",settings_main);



        sub_sections.push_back(new SettingsNetwork(builder));
//        sub_sections.push_back(new SettingsPlugins(builder,PLUGIN_COUNT));
        sub_sections.push_back(new SettingsPlayback(builder));
        sub_sections.push_back(new SettingsGeneral(builder));

        ok_button->signal_clicked().connect(sigc::mem_fun(*this,&Settings::on_button_ok));
        cancel_button->signal_clicked().connect(sigc::mem_fun(*this,&Settings::on_button_cancel));

        on_button_cancel();


    }
    //---------------------------

    Settings::~Settings(void)
    {
        for(unsigned int i=0;i<sub_sections.size();i++)
            delete sub_sections[i];
    }

    //---------------------------

    void Settings::on_button_ok(void)
    {
        for(unsigned int i=0;i< sub_sections.size();i++)
        {
            sub_sections[i]->accept_new_settings();
        }
        CONFIG_SAVE_NOW();

    }
    //---------------------------
    void Settings::on_button_cancel(void)
    {
        for(unsigned int i=0;i< sub_sections.size();i++)
        {
            sub_sections[i]->decline_new_settings();
        }

    }
    //---------------------------
    Gtk::Widget* Settings::get_container(void)
    {
        return settings_main;
    }
    //---------------------------

}
