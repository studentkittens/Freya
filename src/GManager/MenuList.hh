#ifndef FREYA_MENULIST_GUARD
#define FREYA_MENULIST_GUARD

#include <gtkmm.h>
#include "../MPD/Client.hh"
namespace GManager
{
    class MenuList
    {
        public:

            MenuList(MPD::Client &client, const Glib::RefPtr<Gtk::Builder> &builder);
            ~MenuList();

        private:

            void on_connection_update(bool is_connected);
            void on_client_update(enum mpd_idle event, MPD::NotifyData &data);

            void on_menu_connect(void);
            void on_menu_disconnect(void);
            void on_menu_quit(void);

            void on_menu_play(void);
            void on_menu_stop(void);
            void on_menu_prev(void);
            void on_menu_next(void);

            void on_menu_random(void);
            void on_menu_repeat(void);
            void on_menu_single(void);
            void on_menu_consume(void);

            void on_menu_about(void);

            bool running;
            MPD::Client * mp_Client;

            /* Widgets */
            Gtk::MenuItem *menu_connect, *menu_disconnect, *menu_quit,
                          *menu_play, *menu_stop, *menu_prev, *menu_next, *menu_playback, *menu_misc,
                          *menu_about;
            Gtk::CheckMenuItem *menu_random, *menu_repeat, *menu_single, *menu_consume,
                               *menu_log;
            Gtk::AboutDialog * window_about;
    };

}


#endif
