#ifndef FREYA_ARTISTPHOTOMGR_HH
#define FREYA_ARTISTPHOTOMGR_HH

#include <gtkmm.h>
#include "ImageWall.hh"

namespace Browser
{
    class ArtistPhotosMgr : public Gtk::Expander 
    {
        public:
            ArtistPhotosMgr(BaseObjectType* cobject, const Glib::RefPtr<Gtk::Builder>& builder);

        private:
            ImageWall wall;
    };
}

#endif /* end of include guard: FREYA_ARTISTPHOTOMGR_HH */
