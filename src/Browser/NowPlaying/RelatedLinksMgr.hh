#ifndef FREYA_RELATEDLINKSMGR_HH
#define FREYA_RELATEDLINKSMGR_HH

#include <gtkmm.h>
#include "ImageWall.hh"
#include "../../Glyr/UpdateInterface.hh"

namespace Browser
{
class RelatedLinksMgr : public Gtk::Expander, public Glyr::UpdateInterface
{
public:
    RelatedLinksMgr(BaseObjectType* cobject, const Glib::RefPtr<Gtk::Builder>& builder);
    void update(MPD::Client& client, mpd_idle event, MPD::NotifyData& data);
    void on_deliver(GlyrMemCache * list);

private:
    ImageWall txtWall;
};
}

#endif /* end of include guard: FREYA_RELATEDLINKSMGR_HH */
