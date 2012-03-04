#include "TracklistMgr.hh"

namespace Browser
{
    TracklistMgr::TracklistMgr(BaseObjectType* cobject, const Glib::RefPtr<Gtk::Builder>& builder)
        : Gtk::Expander(cobject),
          txtWall(10,3)
    {
        add(txtWall);
        for(int i = 0; i < 10; i++) {
            txtWall.add(*Gtk::manage(new Gtk::LinkButton("http://www.google.de","A Track in the queue")));
        }
    }
}
