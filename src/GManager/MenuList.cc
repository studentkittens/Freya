#include "MenuList.hh"

#include "../Log/Writer.hh"
#include "../Utils/Utils.hh"

#define VOLUME_STEP 5
#define VOLUME_LOW 33
#define VOLUME_MID 66

namespace GManager
{
    MenuList::MenuList(MPD::Client &client, const Glib::RefPtr<Gtk::Builder> &builder) :
        AbstractClientUser(client)
    {
        running=false;
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
        BUILDER_GET(builder,"menu_item_vol_up", menu_vol_inc);
        BUILDER_GET(builder,"menu_item_vol_down", menu_vol_dec);
        BUILDER_GET(builder,"menu_about",menu_about);
        
        BUILDER_GET(builder,"playback_menuitem",menu_playback);
        BUILDER_GET(builder,"misc_menuitem",menu_misc);
       
         BUILDER_ADD(builder,"ui/About.glade");
        BUILDER_GET_NO_MANAGE(builder,"about_main",window_about);

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
        
        menu_vol_inc->signal_activate().connect(sigc::mem_fun(*this,&MenuList::on_menu_vol_inc));
        menu_vol_dec->signal_activate().connect(sigc::mem_fun(*this,&MenuList::on_menu_vol_dec));
        menu_about->signal_activate().connect(sigc::mem_fun(*this,&MenuList::on_menu_about));

        on_connection_change(mp_Client->is_connected());
    }

    //-----------------------------
    MenuList::~MenuList(void)
    {
        if(window_about!=NULL)
        {
            delete window_about;
            window_about=NULL;
        }
    }
    //-----------------------------
    void MenuList::on_menu_connect(void)
    {
        Debug("Connect Menu activated");
        mp_Client->connect();
    }
    //-----------------------------
    void MenuList::on_menu_disconnect(void)
    {
        mp_Client->disconnect();
        Debug("Disconnect Menu activated");
    }
    //-----------------------------
    void MenuList::on_menu_quit(void)
    {
        /* TODO */
        Gtk::Main::quit();
    }
    //-----------------------------
    void MenuList::on_menu_play(void)
    {
        mp_Client->playback_pause();
    }
    //-----------------------------
    void MenuList::on_menu_stop(void)
    {
        mp_Client->playback_stop();
    }
    //-----------------------------
    void MenuList::on_menu_prev(void)
    {
        mp_Client->playback_prev();
    }
    //-----------------------------
    void MenuList::on_menu_next(void)
    {
        mp_Client->playback_next();
    }

    //-----------------------------

    void MenuList::on_connection_change(bool is_connected)
    {
        menu_connect->set_sensitive(!is_connected);
        menu_disconnect->set_sensitive(is_connected);
        menu_playback->set_sensitive(is_connected);
        menu_misc->set_sensitive(is_connected);
    }

    //-----------------------------

    void MenuList::on_client_update(enum mpd_idle event, MPD::NotifyData &data)
    {
        if((event & MPD_IDLE_OPTIONS) && !running)
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

    //-----------------------------

    void MenuList::on_menu_random(void)
    {
        if(!running) mp_Client->toggle_random();
    }
    //-----------------------------
    void MenuList::on_menu_repeat(void)
    {
        if(!running) mp_Client->toggle_repeat();
    }
    //-----------------------------
    void MenuList::on_menu_single(void)
    {
        if(!running) mp_Client->toggle_single();
    }
    //-----------------------------
    void MenuList::on_menu_consume(void)
    {
        if(!running) mp_Client->toggle_consume();
    }
    //-----------------------------
    void MenuList::on_menu_about(void)
    {
        window_about->run();
        window_about->hide();
    }
    //-----------------------------
    void MenuList::on_menu_vol_dec(void)
    {
        unsigned curVol = mp_Client->get_status()->get_volume();
        curVol = (curVol < VOLUME_STEP) ? 0 : (curVol - VOLUME_STEP);
    }
    //-----------------------------
    void MenuList::on_menu_vol_inc(void)
    {
        unsigned curVol = mp_Client->get_status()->get_volume();
        curVol = (curVol > (100-VOLUME_STEP)) ? 100 : (curVol + VOLUME_STEP);
    }
}
