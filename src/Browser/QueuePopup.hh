#ifndef FREYA_QUEUE_POPUP_GUARD
#define FREYA_QUEUE_POPUP_GUARD

#include <gtkmm.h>
#include "BasePopup.hh"

namespace Browser
{
    class QueuePopup : public BasePopup 
    {
        public:
            QueuePopup(Gtk::Widget& to_register);

        private:
            Glib::RefPtr<Gtk::Action> m_ActionDel;
            Glib::RefPtr<Gtk::Action> m_ActionPlAdd;
            Glib::RefPtr<Gtk::Action> m_ActionClear;
    };
}
#endif /* end of include guard: FREYA_QUEUE_POPUP_GUARD */
