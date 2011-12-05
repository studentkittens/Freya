#ifndef FREYA_DATABASE_POPUP_GUARD
#define FREYA_DATABASE_POPUP_GUARD

#include <gtkmm.h>
#include "BasePopup.hh"

namespace Browser
{
    class DatabasePopup : public BasePopup 
    {
        public:
            DatabasePopup(Gtk::Widget& to_register);

        private:
            Glib::RefPtr<Gtk::Action> m_ActionAdd;
            Glib::RefPtr<Gtk::Action> m_ActionReplace;
            Glib::RefPtr<Gtk::Action> m_ActionUpdate;
            Glib::RefPtr<Gtk::Action> m_ActionRescan;
    };
}
#endif /* end of include guard: FREYA_DATABASE_POPUP_GUARD */
