#ifndef FREYA_TRACKLIST_HH
#define FREYA_TRACKLIST_HH

#include <gtkmm.h>
#include "ImageWall.hh"

namespace Browser 
{
    class TracklistMgr : public Gtk::Expander
    {
        public:
            TracklistMgr(BaseObjectType* cobject, const Glib::RefPtr<Gtk::Builder>& builder);

        private:
            //Gtk::Box trackBox;
            ImageWall txtWall;
    };
}

#endif /* end of include guard: FREYA_TRACKLIST_HH */

