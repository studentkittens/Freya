#include "TitleLabel.hh"
#include "../Utils/Utils.hh"

namespace GManager
{
    TitleLabel::TitleLabel(MPD::Client& client, const Glib::RefPtr<Gtk::Builder>& builder)
    {
        mp_Client = &client;
        mp_Client->get_notify().connect(sigc::mem_fun(*this,&TitleLabel::on_client_update));

        BUILDER_GET(builder,"title_label",mp_TitleLabel);
        BUILDER_GET(builder,"artist_album_label",mp_ArtistAlbumLabel);
    }

    //----------------

    TitleLabel::~TitleLabel() {}

    //----------------
    
    void TitleLabel::update_next_song_widget(MPD::NotifyData& data)
    {
        // TODO: libmpdclient does not offer this info *aaargh!*
        // mp_Client->get_song_at_id(data.get_status().get_
    }

    //----------------

    void TitleLabel::on_client_update(enum mpd_idle event, MPD::NotifyData& data)
    {
        if(event & (MPD_IDLE_PLAYER))
        {
            MPD::Song& current_song = data.get_song();
            char * title_string = g_markup_printf_escaped("<b>%s</b> (Track %s)",
                    current_song.get_tag(MPD_TAG_TITLE,0),
                    current_song.get_tag(MPD_TAG_TRACK,0)
                    );
            char * artist_album = g_markup_printf_escaped("<small>By <b>%s</b> on <b>%s</b> (%s)</small>",
                    current_song.get_tag(MPD_TAG_ARTIST,0),
                    current_song.get_tag(MPD_TAG_ALBUM,0),
                    current_song.get_tag(MPD_TAG_DATE,0)
                    );

            mp_TitleLabel->set_markup_with_mnemonic(title_string); 
            mp_ArtistAlbumLabel->set_markup_with_mnemonic(artist_album); 
            g_free(artist_album);
            g_free(title_string);
        }
    }
}
