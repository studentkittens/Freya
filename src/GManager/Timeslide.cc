#include "Timeslide.hh"
#include "../Log/Writer.hh"

namespace GManager
{
    Timeslide::Timeslide(const Glib::RefPtr<Gtk::Builder>& builder)
    {
        try
        {
            builder->get_widget("time_slide",m_Timeslide);
            Gtk::manage(m_Timeslide);
            m_Timeslide->set_range(0.0,100.0);
            Glib::signal_timeout().connect(sigc::mem_fun(*this,&Timeslide::tick), 1000);

        }
        catch(const Gtk::BuilderError& e)
        {
            Error("BuilderFailure: %s",e.what().c_str());
        }
    }

    /* ------------------ */

    Timeslide::~Timeslide(void) {}

    /* ------------------ */

    gboolean Timeslide::tick(void)
    {
        m_Timeslide->set_value(m_Timeslide->get_value() + 1.0);
        return TRUE;
    }
}
