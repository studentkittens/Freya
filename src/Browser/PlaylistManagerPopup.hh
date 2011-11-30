#ifndef FREYA_PLMANAGER_POPUP_GUARD
#define FREYA_PLMANAGER_POPUP_GUARD

#include <gtkmm.h>
#include "BasePopup.hh"

namespace Browser
{
    class PlaylistManagerPopup : public BasePopup 
    {
        public:
            PlaylistManagerPopup(Gtk::Widget& to_register);

        private:
            Glib::RefPtr<Gtk::Action> m_ActionAdd;
            Glib::RefPtr<Gtk::Action> m_ActionDel;
            Glib::RefPtr<Gtk::Action> m_ActionRepl;
            Glib::RefPtr<Gtk::Action> m_ActionRename;
    };
}
#endif 
