#include "Trayicon.hh"
#include "../Log/Writer.hh"
#include "../Config/Handler.hh"
namespace GManager 
{
    Trayicon::Trayicon(MPD::Client& client,Gtk::Window& main_window) :
        Gtk::StatusIcon(Gtk::Stock::INFO)
    {
        mp_Client = &client;
        mp_Window = &main_window;
        set_visible(CONFIG_GET_AS_INT("settings.trayicon.totray"));

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
}
