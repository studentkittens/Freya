#ifndef FREYA_FORTUNA_GUARD
#define FREYA_FORTUNA_GUARD

#include "../AbstractBrowser.hh"
#include <gtkmm.h>

namespace Browser
{
    class Fortuna : public AbstractBrowser
    {
        public:
       
            Fortuna(Glib::RefPtr<Gtk::Builder>& builder);

            /* Implemented from AbstractBrowser */
            Gtk::Widget * get_container(void);

        private:

            /* Workers */
            Glib::ustring get_fortune(void);
            void on_refresh_fortune(void);

            /* Widgets */
            Gtk::ScrolledWindow * mp_FortuneScroll;
            Gtk::Label * mp_FortuneLabel;
            Gtk::Button * mp_FortuneRefresh;
    };
}


#endif /* end of include guard: FREYA_FORTUNA_GUARD */
