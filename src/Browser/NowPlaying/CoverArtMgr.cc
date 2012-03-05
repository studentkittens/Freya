#include "CoverArtMgr.hh"
#include "../../Utils/Utils.hh"

namespace Browser
{
    CoverArtMgr::CoverArtMgr(BaseObjectType* cobject, const Glib::RefPtr<Gtk::Builder>& builder)
        : Gtk::Expander(cobject),
          coverArt(NULL)
    {
        BUILDER_GET(builder,"np_ArtistLabel",mp_ArtistLabel);
        BUILDER_GET(builder,"np_AlbumLabel", mp_AlbumLabel);
        BUILDER_GET(builder,"np_TitleLabel", mp_TitleLabel);
        BUILDER_GET(builder,"np_YearLabel",  mp_YearLabel);

        //TODO
        Gtk::Box * coverartBox;
        BUILDER_GET(builder,"np_coverartbox",coverartBox);
        coverArt = new EventImage();
        coverartBox->pack_start(*coverArt,true,false);
        coverArt->set_size_request(150,150);
        coverartBox->show_all();
    }
    
    /////////////////////////////
    
    CoverArtMgr::~CoverArtMgr()
    {
        delete coverArt;
    }
    
    /////////////////////////////
    
    void CoverArtMgr::update(MPD::Client& client, mpd_idle events, MPD::NotifyData& data)
    {
        if(events & MPD_IDLE_PLAYER) {
            MPD::Song * curr = data.get_song();
            if(curr != NULL) {
                mp_ArtistLabel->set_text(curr->get_tag(MPD_TAG_TITLE,0));
                mp_AlbumLabel ->set_text(curr->get_tag(MPD_TAG_ARTIST,0));
                mp_TitleLabel ->set_text(curr->get_tag(MPD_TAG_ALBUM,0));
                mp_YearLabel  ->set_text(curr->get_tag(MPD_TAG_DATE,0));
            } else {
                mp_ArtistLabel->set_text("[Not Playing]");
                mp_AlbumLabel ->set_text("");
                mp_TitleLabel ->set_text("");
                mp_YearLabel  ->set_text("");
            }
        }
    }
}
