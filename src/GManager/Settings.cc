#include "Settings.hh"
#include "../Utils/Utils.hh"

#define SUBSECTION_COUNT 4;

namespace GManager
{
    Settings:Settings(const Glib::RefPtr<Gtk::Builder> &builder)
    {
        Glib::ustring settings_file("ui/Settings.glade");

        sub_sections = new SettingsSub[SUBSECTION_COUNT];
        sub_sections[0] = new SettingsNetwork(builder);
        sub_sections[1] = new SettingsPlugins(builder);
        sub_sections[2] = new SettingsReplay(builder);
        sub_sections[3] = new SettingsGeneral(builder);

        BUILDER_ADD(builder,settings_file);
        BUILDER_GET(builder,"ok_button",ok_button);
        BUILDER_GET(builder,"stop_button",stop_button);

        ok_button->signal_clicked().connect(sigc::mem_fun(*this,&Settings::on_button_ok));
        stop_button->signal_clicked().connect(sigc::mem_fun(*this,&Settings::on_button_stop));



    }
    //---------------------------

    Settings::~Settings(void)
    {
        if(sub_section != NULL)
        {
            for(int i=0;i<SUBSECTION_COUNT;i++)
            {
                if(sub_section[i] != NULL)
                {
                    delete sub_section[i];
                    sub_section[i] = NULL;
                }
            }
            delete[] sub_section;
        }

    }

    //---------------------------

    void Settings::on_button_ok(void)
    {
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

}
