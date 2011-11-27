#include "Trayicon.hh"
#include "../Log/Writer.hh"

namespace GManager 
{
    Trayicon::Trayicon(MPD::Client& client,Gtk::Window& main_window) :
        Gtk::StatusIcon(Gtk::Stock::INFO)
    {
        mp_Client = &client;
        mp_Window = &main_window;

        set_tooltip_text("Freya Trayicon");
        Info("Created TrayIcon");
    }

    Trayicon::~Trayicon(void)
    {
    }

    void Trayicon::on_activate(void)
    {
        g_message("Clicked.");
        mp_Window->set_visible(!mp_Window->get_visible());
    }

    void Trayicon::on_popup_menu(guint button, guint32 activate_time)
    {
        g_message("Popup.");
    }
    
    //-----------------------------
    void MenuList::on_menu_quit(void)
    {
        /* TODO */
        exit(0);
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

}
