#include "ArtistPhotosMgr.hh"
#include "../../Utils/Utils.hh"
#include "../../Glyr/Request.hh"

namespace Browser
{
ArtistPhotosMgr::ArtistPhotosMgr(BaseObjectType* cobject, const Glib::RefPtr<Gtk::Builder>& builder)
    : Gtk::Expander(cobject),
      wall(7,3)
{
    add(wall);
    show_all();
}

/////////////////////////////

void ArtistPhotosMgr::on_deliver(GlyrMemCache * list)
{
    for(GlyrMemCache * iter = list; iter; iter = iter->next)
    {
        wall.add(iter,120,120,true);
    }
    glyr_free_list(list);
}

/////////////////////////////

void ArtistPhotosMgr::update(MPD::Client& client, mpd_idle event, MPD::NotifyData& data)
{
    if(event & MPD_IDLE_PLAYER)
    {
        wall.clear();
        MPD::Song * curr = data.get_song();
        if(curr != NULL)
        {
            Glyr::Stack::instance().request(this,*curr,GLYR_GET_ARTIST_PHOTOS,6);
        }
    }
}
}
