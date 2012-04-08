#ifndef FREYA_ARTISTPHOTOMGR_HH
#define FREYA_ARTISTPHOTOMGR_HH

#include <gtkmm.h>
#include "ImageWall.hh"
#include "../../Glyr/UpdateInterface.hh"

namespace Browser
{
class ArtistPhotosMgr : public Gtk::Expander, public Glyr::UpdateInterface
{
public:
    ArtistPhotosMgr(BaseObjectType* cobject, const Glib::RefPtr<Gtk::Builder>& builder);
    void update(MPD::Client& client, mpd_idle event, MPD::NotifyData& data);
    void on_deliver(GlyrMemCache * list);

private:
    ImageWall wall;
};
}

#endif /* end of include guard: FREYA_ARTISTPHOTOMGR_HH */
