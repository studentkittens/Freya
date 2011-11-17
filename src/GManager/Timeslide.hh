#ifndef FREYA_TIMESLIDE_GUARD
#define FREYA_TIMESLIDE_GUARD

#include <gtkmm.h>
#include "ClientTimerProxy.hh"

namespace GManager
{
    class Timeslide 
    {
        public:

            Timeslide(ClientTimerProxy& tproxy, const Glib::RefPtr<Gtk::Builder>& builder);
            ~Timeslide();

        private:

            void tick(double time);

            Gtk::Scale * m_Timeslide;

    };
}
#endif
