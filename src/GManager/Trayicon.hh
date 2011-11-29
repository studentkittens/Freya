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

        private:

            void add_item(Glib::RefPtr<Gtk::Action>& action,
                    Glib::ustring item_name,
                    Glib::ustring item_label,
                    Glib::ustring item_tooltip,
                    Gtk::StockID icon);

            void on_activate(void);
            void on_popup_menu (guint button, guint32 activate_time);

            void on_next_clicked(void);
            void on_prev_clicked(void);
            void on_stop_clicked(void);
            void on_pause_clicked(void);
            void on_quit_clicked(void);

            Gtk::Menu * m_Popup;
            Glib::RefPtr<Gtk::UIManager> m_refUIManager;
            Glib::RefPtr<Gtk::ActionGroup> m_refActionGroup;
            Glib::RefPtr<Gtk::Action> m_ActionNext;
            Glib::RefPtr<Gtk::Action> m_ActionPrev;
            Glib::RefPtr<Gtk::Action> m_ActionStop;
            Glib::RefPtr<Gtk::Action> m_ActionPause;
            Glib::RefPtr<Gtk::Action> m_ActionQuit;

            Gtk::Window * mp_Window;
            MPD::Client * mp_Client;
    };
}
#endif /* end of include guard: FREYA_TRAYICON_GUARD */
