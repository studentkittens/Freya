#include "TitleLabel.hh"
#include "../Utils/Utils.hh"
#include "../Notify/Notify.hh"
namespace GManager
{
    TitleLabel::TitleLabel(MPD::Client& client, const Glib::RefPtr<Gtk::Builder>& builder)
        : AbstractClientUser(client)
    {
        BUILDER_GET(builder,"title_label",mp_TitleLabel);
        BUILDER_GET(builder,"artist_album_label",mp_ArtistAlbumLabel);
        BUILDER_GET(builder,"next_song_artist",mp_NextSongArtistLabel);
        BUILDER_GET(builder,"next_song_title",mp_NextSongTitleLabel);
    }

    //----------------
    
    void TitleLabel::update_next_song_widget(MPD::NotifyData& data)
    {
        MPD::Song& current_song = data.get_next_song(); 
        char * title_string = g_markup_printf_escaped("<small>%s</small>",
                current_song.get_tag(MPD_TAG_TITLE,0)
                );
        char * artist_string = g_markup_printf_escaped("<small>%s</small>",
                current_song.get_tag(MPD_TAG_ARTIST,0)
                );

        mp_NextSongArtistLabel->set_markup(artist_string);
        mp_NextSongTitleLabel->set_markup(title_string);

        g_free(title_string);
        g_free(artist_string);
    }

    //----------------
    
    void TitleLabel::on_connection_change(bool is_connected)
    {
        /* Empty for now */
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
            char * artist_album = g_markup_printf_escaped("<small>by <b>%s</b> on <b>%s</b> (%s)</small>",
                    current_song.get_tag(MPD_TAG_ARTIST,0),
                    current_song.get_tag(MPD_TAG_ALBUM,0),
                    current_song.get_tag(MPD_TAG_DATE,0)
                    );

            mp_TitleLabel->set_markup(title_string); 
            mp_ArtistAlbumLabel->set_markup(artist_album); 

            g_free(artist_album);
            g_free(title_string);
        }

        if(event & (MPD_IDLE_PLAYER|MPD_IDLE_OPTIONS))
        {
            update_next_song_widget(data);
        }
    }
}
