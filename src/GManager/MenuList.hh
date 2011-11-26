#ifndef FREYA_MENULIST_GUARD
#define FREYA_MENULIST_GUARD

#include <gtkmm.h>
#include "../MPD/Clients.hh"
namespace GManager
{
    class MenuList
    {
        public:

            MenuList(MPD::Client &client, const Glib::RefPtr<Gtk::Builder> &builder);
            ~MenuList();

        private:

            /* Widgets */
            Gtk::MenuItem *menu_connect, *menu_disconnect, *menu_quit,
                          *menu_play, *menu_stop, *menu_prev, *menu_next, *menu_mode,
                          *menu_about;
            Gtk::CheckMenuItem *menu_random, *menu_repeat, *menu_single, *menu_consume,
                               *menu_log;
    }

}


#endif
