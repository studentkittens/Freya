#ifndef FREYA_TRAYICON_GUARD
#define FREYA_TRAYICON_GUARD

#include <gtkmm.h>
#include "../MPD/Client.hh"
#include "../Browser/BasePopup.hh"
#include "../AbstractClientUser.hh"

namespace GManager
{
    class Trayicon : public Gtk::StatusIcon, public Browser::BasePopup, public AbstractClientUser
    {
        public:
            Trayicon(MPD::Client& client,Gtk::Window& main_window);

        private:

            void on_activate(void);
            void on_popup_menu (guint button, guint32 activate_time);

            void on_connection_change(bool is_connected);
            void on_client_update(enum mpd_idle event, MPD::NotifyData& data);

            void on_next_clicked(void);
            void on_prev_clicked(void);
            void on_stop_clicked(void);
            void on_pause_clicked(void);
            void on_quit_clicked(void);

            Glib::RefPtr<Gtk::Action> m_ActionNext;
            Glib::RefPtr<Gtk::Action> m_ActionPrev;
            Glib::RefPtr<Gtk::Action> m_ActionStop;
            Glib::RefPtr<Gtk::Action> m_ActionPause;
            Glib::RefPtr<Gtk::Action> m_ActionQuit;
            Gtk::Window * mp_Window;
    };
}
#endif /* end of include guard: FREYA_TRAYICON_GUARD */
