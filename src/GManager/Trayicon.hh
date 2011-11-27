#ifndef FREYA_TRAYICON_GUARD
#define FREYA_TRAYICON_GUARD

#include <gtkmm.h>
#include "../MPD/Client.hh"

namespace GManager
{
    class Trayicon : public Gtk::StatusIcon
    {
        public:
            Trayicon(MPD::Client& client,Gtk::Window& main_window);
            ~Trayicon(void);

        private:

            void on_activate(void);
            void on_popup_menu (guint button, guint32 activate_time);

            Gtk::Window * mp_Window;
            MPD::Client * mp_Client;
    };
}

#endif /* end of include guard: FREYA_TRAYICON_GUARD */
