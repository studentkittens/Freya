#ifndef FREYA_ARTISTPHOTOMGR_HH
#define FREYA_ARTISTPHOTOMGR_HH

#include <gtkmm.h>
#include "ImageWall.hh"
#include "UpdateInterface.hh"

namespace Browser
{
    class ArtistPhotosMgr : public Gtk::Expander, public UpdateInterface
    {
        public:
            ArtistPhotosMgr(BaseObjectType* cobject, const Glib::RefPtr<Gtk::Builder>& builder);
            void update(MPD::Client& client, mpd_idle event, MPD::NotifyData& data);

        private:
            ImageWall wall;
    };
}

#endif /* end of include guard: FREYA_ARTISTPHOTOMGR_HH */
