#ifndef FREYA_DISCONNECT_MANAGER
#define FREYA_DISCONNECT_MANAGER

#include <gtkmm.h>
#include "../MPD/Client.hh"
#include "../Utils/Utils.hh"
#include "../Log/Writer.hh"

namespace GManager
{
    class DisconnectManager
    {
        public:
            DisconnectManager(MPD::Client& client, Gtk::Window * main_window,
                    const Glib::RefPtr<Gtk::Builder> &builder);

        private:

            void on_connection_change(bool is_connected);

            MPD::Client * mp_Client;
            Gtk::Window * mp_Window;
            Gtk::Box * mp_Top_Box;
            Gtk::Box * mp_Main_Paned;
    };
}

#endif
