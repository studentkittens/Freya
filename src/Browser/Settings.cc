#include "Settings.hh"
#include "../Utils/Utils.hh"
#include "../Log/Writer.hh"

namespace Browser
{
    Settings::Settings(const Glib::RefPtr<Gtk::Builder> &builder):
        AbstractBrowser("Settings",Gtk::Stock::PREFERENCES)
    {
        BUILDER_ADD(builder,"ui/Settings.glade");
        BUILDER_GET(builder,"ok_button",ok_button);
        BUILDER_GET(builder,"cancel_button",cancel_button);
        BUILDER_GET(builder,"reset_button",reset_button);
        BUILDER_GET(builder,"settings_main",settings_main);



        sub_sections.push_back(new SettingsNetwork(builder, this));
        sub_sections.push_back(new SettingsPlayback(builder, this));
        sub_sections.push_back(new SettingsGeneral(builder, this));

        ok_button->signal_clicked().connect(sigc::mem_fun(*this,&Settings::on_button_ok));
        cancel_button->signal_clicked().connect(sigc::mem_fun(*this,&Settings::on_button_cancel));
        reset_button->signal_clicked().connect(sigc::mem_fun(*this,&Settings::on_button_reset));

        on_button_cancel();

        ok_button->set_sensitive(false);
        cancel_button->set_sensitive(false);

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
        ok_button->set_sensitive(false);
        cancel_button->set_sensitive(false);

    }
    //---------------------------
    void Settings::on_button_cancel(void)
    {
        for(unsigned int i=0;i< sub_sections.size();i++)
        {
            sub_sections[i]->decline_new_settings();
        }
        ok_button->set_sensitive(false);
        cancel_button->set_sensitive(false);
    }
    //---------------------------
    Gtk::Widget* Settings::get_container(void)
    {
        return settings_main;
    }
    //---------------------------
    void Settings::on_button_reset(void)
    {
        for(unsigned int i=0;i< sub_sections.size();i++)
        {
            sub_sections[i]->reset_settings();
        }
    }
    //--------------------------
    void Settings::settings_changed(void)
    {
        ok_button->set_sensitive(true);
        cancel_button->set_sensitive(true);
    }
}
