#ifndef FREYA_OTHERALBUMS_HH
#define FREYA_OTHERALBUMS_HH

#include <gtkmm.h>
#include "ImageWall.hh"

namespace Browser 
{
    class OtherAlbumsMgr : public Gtk::Expander
    {
        public:
            OtherAlbumsMgr(BaseObjectType* cobject, const Glib::RefPtr<Gtk::Builder>& builder);

        private:
            ImageWall wall;
    };
}

#endif /* end of include guard: FREYA_OTHERALBUMS_HH */

