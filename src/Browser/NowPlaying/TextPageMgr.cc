#include "TextPageMgr.hh"
#include "../../Utils/Utils.hh"
#include "../../Glyr/Request.hh"

namespace Browser
{
    TextPageMgr::TextPageMgr(BaseObjectType* cobject, const Glib::RefPtr<Gtk::Builder>& builder)
        : Gtk::ScrolledWindow(cobject)
    {
        BUILDER_GET(builder,"textview",textView);
    }
    
    ////////////////////

    void TextPageMgr::on_deliver(GlyrMemCache * list)
    {
        if(list != NULL) {
            Glib::ustring text(list->data);
            textView->get_buffer()->set_text(text);
        } else {
            Glib::ustring text("Not found.");
            textView->get_buffer()->set_text(text);
        }
    }

    ////////////////////
            
    void TextPageMgr::update(MPD::Client& client, mpd_idle events, MPD::NotifyData& data)
    {
        if(events & MPD_IDLE_PLAYER) 
        {
            MPD::Song * curr = data.get_song();
            if(curr != NULL) {
                Glyr::Stack::instance().request(this,*curr,type);
            }
        }
    }
    
    ////////////////////
            
    void TextPageMgr::set_request_type(GLYR_GET_TYPE type)
    {
        this->type = type;
    }
}
