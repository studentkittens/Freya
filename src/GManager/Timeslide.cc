#include "Timeslide.hh"
#include "../Log/Writer.hh"
#include "../Utils/Utils.hh"

namespace GManager
{
    Timeslide::Timeslide(ClientTimerProxy& tproxy, const Glib::RefPtr<Gtk::Builder>& builder)
    {
        BUILDER_GET(builder,"time_slide",m_Timeslide);
        m_Timeslide->set_range(0.0,100.0);
        tproxy.get_notify().connect(sigc::mem_fun(*this,&Timeslide::tick));
    }

    /* ------------------ */

    Timeslide::~Timeslide(void) {}

    /* ------------------ */

    void Timeslide::tick(double time)
    {
        m_Timeslide->set_value(time);
    }
}
