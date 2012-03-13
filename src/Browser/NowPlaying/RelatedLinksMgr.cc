#include "RelatedLinksMgr.hh"
#include "../../Glyr/Request.hh"

namespace Browser
{
    RelatedLinksMgr::RelatedLinksMgr(BaseObjectType* cobject, const Glib::RefPtr<Gtk::Builder>& builder)
        : Gtk::Expander(cobject),
          txtWall(10,2)
    {
        add(txtWall);
    }

    /////////////////////////////////
    
    void RelatedLinksMgr::on_deliver(GlyrMemCache * list)
    {
        txtWall.clear();
        for(GlyrMemCache * iter = list; iter; iter = iter->next) {
            char ** arr = g_strsplit(iter->data,":",2);
            if(arr && arr[0] && arr[1]) {
                txtWall.add(*Gtk::manage(new Gtk::LinkButton(arr[1],arr[0])));
            }
        }
        glyr_free_list(list);
    }
    
    /////////////////////////////////

    void RelatedLinksMgr::update(MPD::Client& client, mpd_idle event, MPD::NotifyData& data)
    {
        MPD::Song * curr = data.get_song();
        if(curr != NULL) {
            Glyr::Stack::instance().request(this,curr->get_tag(MPD_TAG_ARTIST,0),NULL,NULL,GLYR_GET_RELATIONS,10);
        }
    }
}
