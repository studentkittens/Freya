#include "ArtistPhotosMgr.hh"
#include "../../Utils/Utils.hh"

namespace Browser
{
    ArtistPhotosMgr::ArtistPhotosMgr(BaseObjectType* cobject, const Glib::RefPtr<Gtk::Builder>& builder)
        : Gtk::Expander(cobject),
          wall(7,3)
    {
        add(wall);
        for(int i = 0; i < 3; i++) {
            char * s = g_strdup_printf("ui/Akrea_artistphoto_%d.jpeg",i);
            puts(s);
            std::string a(s);
            wall.add(a);
        }
        show_all();
    }
    
    /////////////////////////////
    
    void ArtistPhotosMgr::update(MPD::Client& client, mpd_idle event, MPD::NotifyData& data)
    {

    }
}
