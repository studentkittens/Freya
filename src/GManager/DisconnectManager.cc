#include "DisconnectManager.hh"

namespace GManager
{
    DisconnectManager::DisconnectManager(MPD::Client& client, Gtk::Window * main_window, const Glib::RefPtr<Gtk::Builder> &builder)
    {
        mp_Window = main_window;
        mp_Client = &client;
        mp_Client->signal_connection_change().connect(sigc::mem_fun(*this,&DisconnectManager::on_connection_change));
        BUILDER_GET(builder,"main_paned",mp_Main_Paned);
        BUILDER_GET(builder,"top_box",mp_Top_Box);
    }


    void DisconnectManager::on_connection_change(bool is_connected)
    {
        if(is_connected)
        {
            Info("Got reconnected - unlocking gui");
            mp_Main_Paned->set_sensitive(true);
            mp_Top_Box->set_sensitive(true);
        }
        else
        {
            Info("Got disconnected - locking gui");
            mp_Main_Paned->set_sensitive(false);
            mp_Top_Box->set_sensitive(false);
        }
    }
}
