#include "Settings.hh"
#include "../Utils/Utils.hh"
#include "../Log/Writer.hh"

#define SUBSECTION_COUNT 4
#define PLUGIN_COUNT 4
namespace Browser
{
    Settings::Settings(const Glib::RefPtr<Gtk::Builder> &builder):
        AbstractBrowser("Settings"),
        sub_sections(SUBSECTION_COUNT)
    {
        BUILDER_ADD(builder,"ui/Settings.glade");
        BUILDER_GET(builder,"ok_button",ok_button);
        BUILDER_GET(builder,"cancel_button",cancel_button);
        BUILDER_GET(builder,"settings_main",settings_main);

        sub_sections.push_back(SettingsNetwork(builder));
//        sub_sections.push_back(SettingsPlugins(builder,PLUGIN_COUNT));
        sub_sections.push_back(SettingsPlayback(builder));
        sub_sections.push_back(SettingsGeneral(builder));


        ok_button->signal_clicked().connect(sigc::mem_fun(*this,&Settings::on_button_ok));
        cancel_button->signal_clicked().connect(sigc::mem_fun(*this,&Settings::on_button_cancel));



    }
    //---------------------------

    Settings::~Settings(void)
    {
    }

    //---------------------------

    void Settings::on_button_ok(void)
    {

        for(int i=0;i<SUBSECTION_COUNT;i++)
        {
            sub_sections[i].accept_new_settings();
        }

    }
    //---------------------------
    void Settings::on_button_cancel(void)
    {
        for(int i=0;i<SUBSECTION_COUNT;i++)
        {
            sub_sections[i].decline_new_settings();
        }

    }
    //---------------------------
    Gtk::Widget* Settings::get_container(void)
    {
        return settings_main;
    }
    //---------------------------

}
