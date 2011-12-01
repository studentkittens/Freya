#ifndef FREYA_ABSTRACT_POPUP
#define FREYA_ABSTRACT_POPUP

#include <gtkmm.h>

namespace Browser
{
    class BasePopup
    {
        public:

            BasePopup(Gtk::Widget * to_register, Glib::ustring& ui_definition);
            bool menu_popup(GdkEventButton * event);

            /**
             * @brief Get a signal proxy of a certain Gtk::Action in the menu
             *
             * @param name The name of the menu.
             *
             * @return a signal proxy, on which you can call connect()
             */
            Glib::SignalProxy0<void> get_action(Glib::ustring name);

        protected:

            Glib::RefPtr<Gtk::UIManager> m_refUIManager;
            Glib::RefPtr<Gtk::ActionGroup> m_refActionGroup; 
            Glib::ustring * m_UiDefinition;
            Gtk::Menu * mp_Popup;

            void menu_add_item(Glib::RefPtr<Gtk::Action>& action,
                    Glib::ustring item_name,
                    Glib::ustring item_label,
                    Glib::ustring item_tooltip,
                    Gtk::StockID icon);

            /**
             * @brief Call this when done with adding actions
             *        Convention: Menu must be called "PopMenu" in def.
             */
            void menu_construct(Glib::ustring menu_name);
    };
}

#endif /* end of include guard: FREYA_ABSTRACT_POPUP */
