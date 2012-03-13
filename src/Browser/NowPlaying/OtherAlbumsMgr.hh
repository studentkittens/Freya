#ifndef FREYA_OTHERALBUMS_HH
#define FREYA_OTHERALBUMS_HH

#include <gtkmm.h>
#include "ImageWall.hh"
#include "../../Glyr/UpdateInterface.hh"

namespace Browser 
{
    class OtherAlbumsMgr : public Gtk::Expander, public Glyr::UpdateInterface
    {
        public:
            OtherAlbumsMgr(BaseObjectType* cobject, const Glib::RefPtr<Gtk::Builder>& builder);
            void update(MPD::Client& client, mpd_idle event, MPD::NotifyData& data);
            void on_deliver(GlyrMemCache * list);

        private:
            ImageWall wall;
    };
}

#endif /* end of include guard: FREYA_OTHERALBUMS_HH */

