#include "Statusbar.hh"
#include "../Log/Writer.hh"

namespace GManager
{
    Statusbar::Statusbar(const Glib::RefPtr<Gtk::Builder>& builder)
    {
        try
        {
            builder->get_widget("statusbar",m_Statusbar);
            Gtk::manage(m_Statusbar);
            m_Statusbar->push("This the statusbar");
        }
        catch(const Gtk::BuilderError& e)
        {
            Error("BuilderFailure: %s",e.what().c_str());
        }
    }

    /* ------------------ */

    Statusbar::~Statusbar(void) {}
}
