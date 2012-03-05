#include "TextPageMgr.hh"
#include "../../Utils/Utils.hh"

namespace Browser
{
    TextPageMgr::TextPageMgr(BaseObjectType* cobject, const Glib::RefPtr<Gtk::Builder>& builder)
        : Gtk::ScrolledWindow(cobject)
    {
        BUILDER_GET(builder,"textview",textView);
    }

    ////////////////////
}
