#ifndef FREYA_TIMESLIDE_GUARD
#define FREYA_TIMESLIDE_GUARD

#include <gtkmm.h>

namespace GManager
{
    class Timeslide 
    {
        public:

            Timeslide(const Glib::RefPtr<Gtk::Builder>& builder);
            ~Timeslide();

        private:

            Gtk::Scale * m_Timeslide;

            gboolean tick(void);
    };
}
#endif
