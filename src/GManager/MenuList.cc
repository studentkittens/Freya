#include "MenuList.hh"

#include "../Log/Writer.hh"
#include "../Utils/Utils.hh"

namespace GManager
{
    MenuList::MenuList(MPD::Client &client, const Glib::RefPtr<Gtk::Builder> &builder)
    {
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

        BUILDER_GET(builder,"playback_menuitem",menu_playback);
        BUILDER_GET(builder,"misc_menuitem",menu_misc);

        menu_connect->signal_activate().connect(sigc::mem_fun(*this,&MenuList::on_menu_connect));
        menu_disconnect->signal_activate().connect(sigc::mem_fun(*this,&MenuList::on_menu_disconnect));
        menu_quit->signal_activate().connect(sigc::mem_fun(*this,&MenuList::on_menu_quit));

        menu_play->signal_activate().connect(sigc::mem_fun(*this,&MenuList::on_menu_play));
        menu_stop->signal_activate().connect(sigc::mem_fun(*this,&MenuList::on_menu_stop));
        menu_prev->signal_activate().connect(sigc::mem_fun(*this,&MenuList::on_menu_prev));
        menu_next->signal_activate().connect(sigc::mem_fun(*this,&MenuList::on_menu_next));


        mp_Client->signal_connection_change().connect(sigc::mem_fun(*this,&MenuList::on_connection_update));
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
}
