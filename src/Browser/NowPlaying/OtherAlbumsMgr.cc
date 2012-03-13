#include "OtherAlbumsMgr.hh"
#include "EventImage.hh"
#include "../../MPD/BaseClient.hh"
#include "../../Glyr/Request.hh"

namespace Browser 
{
    OtherAlbumsMgr::OtherAlbumsMgr(BaseObjectType* cobject, const Glib::RefPtr<Gtk::Builder>& builder)
        : Gtk::Expander(cobject), 
          wall(5,4)
    {
        add(wall);
    }
    
    /////////////////////////////////
    
    void OtherAlbumsMgr::on_deliver(GlyrMemCache * list)
    {
        if(list != NULL) {
            EventImage * img = new EventImage();
            if(img != NULL) {
                img->set(list->data,list->size,100,100);
                wall.add(*img);
            }
        }
    }

    /////////////////////////////////

    void OtherAlbumsMgr::update(MPD::Client& client, mpd_idle event, MPD::NotifyData& data)
    {
        if(event & MPD_IDLE_PLAYER) 
        {
            MPD::Song  * curr = data.get_song(); 
            if(curr != NULL) 
            {
                MPD::Query * dbq  = client.create_db_tag_query(MPD_TAG_ALBUM);
                if(dbq != NULL)
                {
                    wall.clear();
                    MPD::TagVector list;
                    const char * artist = curr->get_tag(MPD_TAG_ARTIST);

                    dbq->add_tag_constraint(MPD_TAG_ARTIST,artist);      
                    dbq->commit(list);


                    for(MPD::TagVector::iterator it = list.begin(); it != list.end(); it++) 
                    {
                        const char * album = (char*)(*it);
                        if(strcmp(album,curr->get_tag(MPD_TAG_ALBUM)) != 0) {
                            Glyr::Stack::instance().enqueue(this);
                            Glyr::Stack::instance().request(this,artist,album,NULL,GLYR_GET_COVERART);
                        }
                    }
                    delete dbq;
                }
            }
        }
    }
}
