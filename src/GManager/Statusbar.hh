#ifndef FREYA_STATUSBAR_GUARD
#define FREYA_STATUSBAR_GUARD

#include <gtkmm.h>

namespace GManager
{
    class Statusbar
    {
        public:

            Statusbar(const Glib::RefPtr<Gtk::Builder>& builder);
            ~Statusbar();

        private:

            Gtk::Statusbar * m_Statusbar;
    };
}
#endif
