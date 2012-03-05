#ifndef FREYA_RELATEDLINKSMGR_HH
#define FREYA_RELATEDLINKSMGR_HH

#include <gtkmm.h>
#include "ImageWall.hh"
#include "UpdateInterface.hh"

namespace Browser 
{
    class RelatedLinksMgr : public Gtk::Expander, public UpdateInterface
    {
        public:
            RelatedLinksMgr(BaseObjectType* cobject, const Glib::RefPtr<Gtk::Builder>& builder);
            void update(MPD::Client& client, mpd_idle event, MPD::NotifyData& data);

        private:
            ImageWall txtWall;
    };
}

#endif /* end of include guard: FREYA_RELATEDLINKSMGR_HH */
