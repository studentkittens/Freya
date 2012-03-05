#include "OtherAlbumsMgr.hh"

namespace Browser 
{
    OtherAlbumsMgr::OtherAlbumsMgr(BaseObjectType* cobject, const Glib::RefPtr<Gtk::Builder>& builder)
        : Gtk::Expander(cobject), 
          wall(5,4)
    {
        add(wall);
        for(int i = 0; i < 10; i++) {
            char * s = g_strdup_printf("img/Akrea_Lebenslinie_cover_%d.jpeg",i);
            puts(s);
            std::string a(s);
            wall.add(a);
        }
        show_all();
    }
    
    /////////////////////////////////

    void OtherAlbumsMgr::update(MPD::Client& client, mpd_idle event, MPD::NotifyData& data)
    {
    }
}
