#include "TextView.hh"
#include "../../Utils/Utils.hh"

namespace Browser 
{
    TextView::TextView(BaseObjectType* cobject, const Glib::RefPtr<Gtk::Builder>& builder)
        : Gtk::ScrolledWindow(cobject)
    {
        Gtk::TextView * textView;
        BUILDER_GET(builder,"textview",textView);

        Gdk::RGBA transp;
        transp.set_rgba(0,0,0,0.0);
        textView->override_background_color(transp,(Gtk::StateFlags)0xFFFF);
    }
}
