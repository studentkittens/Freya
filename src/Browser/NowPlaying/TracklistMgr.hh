#ifndef FREYA_TRACKLIST_HH
#define FREYA_TRACKLIST_HH

#include <gtkmm.h>
#include "ImageWall.hh"
#include "../../Glyr/UpdateInterface.hh"

namespace Browser 
{
    class TracklistMgr : public Gtk::Expander, public Glyr::UpdateInterface
    {
        public:
            TracklistMgr(BaseObjectType* cobject, const Glib::RefPtr<Gtk::Builder>& builder);
            void update(MPD::Client& client, mpd_idle event, MPD::NotifyData& data);

        private:
            ImageWall txtWall;
    };
}

#endif /* end of include guard: FREYA_TRACKLIST_HH */

