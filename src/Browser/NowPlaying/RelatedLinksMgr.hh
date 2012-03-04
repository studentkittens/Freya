#ifndef FREYA_RELATEDLINKSMGR_HH
#define FREYA_RELATEDLINKSMGR_HH

#include <gtkmm.h>
#include "ImageWall.hh"

namespace Browser 
{
    class RelatedLinks : public Gtk::Expander
    {
        public:
            RelatedLinks(BaseObjectType* cobject, const Glib::RefPtr<Gtk::Builder>& builder);

        private:
            ImageWall txtWall;
    };
}

#endif /* end of include guard: FREYA_RELATEDLINKSMGR_HH */
