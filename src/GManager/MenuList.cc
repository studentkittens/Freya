#include "MenuList.hh"

#include "../Log/Writer.hh"
#include "../Utils/Utils.hh"

namespace GManager
{
    MenuList::MenuList(MPD::Client &client, const Glib::RefPtr<Gtk::Builder> &builder)
    {
        running=false;
        mp_Client = &client;

        BUILDER_GET(builder,"menu_item_connect", menu_connect);
        BUILDER_GET(builder,"menu_item_disconnect", menu_disconnect);
        BUILDER_GET(builder,"menu_item_quit", menu_quit);

        BUILDER_GET(builder,"menu_item_play", menu_play);
        BUILDER_GET(builder,"menu_item_stop", menu_stop);
        BUILDER_GET(builder,"menu_item_prev", menu_prev);
        BUILDER_GET(builder,"menu_item_next", menu_next);

        BUILDER_GET(builder,"menu_mode_repeat", menu_repeat);
        BUILDER_GET(builder,"menu_mode_single", menu_single);
        BUILDER_GET(builder,"menu_mode_random", menu_random);
        BUILDER_GET(builder,"menu_mode_consume", menu_consume);

        BUILDER_GET(builder,"menu_item_log_activate", menu_log);

        BUILDER_GET(builder,"menu_about",menu_about);

        BUILDER_GET(builder,"playback_menuitem",menu_playback);
        BUILDER_GET(builder,"misc_menuitem",menu_misc);

        BUILDER_ADD(builder,"ui/About.glade");
        BUILDER_GET(builder,"about_main",window_about);

        menu_connect->signal_activate().connect(sigc::mem_fun(*this,&MenuList::on_menu_connect));
        menu_disconnect->signal_activate().connect(sigc::mem_fun(*this,&MenuList::on_menu_disconnect));
        menu_quit->signal_activate().connect(sigc::mem_fun(*this,&MenuList::on_menu_quit));

        menu_play->signal_activate().connect(sigc::mem_fun(*this,&MenuList::on_menu_play));
        menu_stop->signal_activate().connect(sigc::mem_fun(*this,&MenuList::on_menu_stop));
        menu_prev->signal_activate().connect(sigc::mem_fun(*this,&MenuList::on_menu_prev));
        menu_next->signal_activate().connect(sigc::mem_fun(*this,&MenuList::on_menu_next));

        menu_random->signal_toggled().connect(sigc::mem_fun(*this,&MenuList::on_menu_random));
        menu_repeat->signal_toggled().connect(sigc::mem_fun(*this,&MenuList::on_menu_repeat));
        menu_single->signal_toggled().connect(sigc::mem_fun(*this,&MenuList::on_menu_single));
        menu_consume->signal_toggled().connect(sigc::mem_fun(*this,&MenuList::on_menu_consume));

        menu_about->signal_activate().connect(sigc::mem_fun(*this,&MenuList::on_menu_about));

        mp_Client->signal_connection_change().connect(sigc::mem_fun(*this,&MenuList::on_connection_update));
        mp_Client->get_notify().connect(sigc::mem_fun(*this,&MenuList::on_client_update));
        on_connection_update(mp_Client->is_connected());
    }

    MenuList::~MenuList(void)
    {
    }
    void MenuList::on_menu_connect(void)
    {
        Debug("Connect Menu activated");
    }
    void MenuList::on_menu_disconnect(void)
    {
        mp_Client->disconnect();
        Debug("Disconnect Menu activated");
    }
    void MenuList::on_menu_quit(void)
    {
        /* TODO */
        exit(0);
    }
    void MenuList::on_menu_play(void)
    {
        mp_Client->playback_pause();
    }
    void MenuList::on_menu_stop(void)
    {
        mp_Client->playback_stop();
    }
    void MenuList::on_menu_prev(void)
    {
        mp_Client->playback_prev();
    }
    void MenuList::on_menu_next(void)
    {
        mp_Client->playback_next();
    }


    void MenuList::on_connection_update(bool is_connected)
    {
        menu_connect->set_sensitive(!is_connected);
        menu_disconnect->set_sensitive(is_connected);

        menu_playback->set_sensitive(is_connected);
        menu_misc->set_sensitive(is_connected);
    }

    void MenuList::on_client_update(enum mpd_idle event, MPD::NotifyData &data)
    {
        if(event && MPD_IDLE_OPTIONS && !running)
        {
            running=true;
            MPD::Status &stat = data.get_status();
            menu_random->set_active(stat.get_random());
            menu_repeat->set_active(stat.get_repeat());
            menu_single->set_active(stat.get_single());
            menu_consume->set_active(stat.get_consume());
            running=false;
        }
    }

    void MenuList::on_menu_random(void)
    {
        if(!running) mp_Client->toggle_random();
    }
    void MenuList::on_menu_repeat(void)
    {
        if(!running) mp_Client->toggle_repeat();
    }
    void MenuList::on_menu_single(void)
    {
        if(!running) mp_Client->toggle_single();
    }
    void MenuList::on_menu_consume(void)
    {
        if(!running) mp_Client->toggle_consume();
    }
    void MenuList::on_menu_about(void)
    {
        window_about->run();
        window_about->hide();
    }
}
