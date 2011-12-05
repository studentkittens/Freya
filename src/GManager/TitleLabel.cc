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
        MPD::Song * current_song = data.get_next_song(); 
        if(current_song != NULL)
        {

            mp_NextSongArtistLabel->set_markup(current_song->song_format("<small>${title}</small>"));
            mp_NextSongTitleLabel->set_markup(current_song->song_format("<small>${artist}</small>"));

        }
        else
        {
            mp_NextSongArtistLabel->set_markup("<small>No next Artist</small>");
            mp_NextSongTitleLabel->set_markup("<small>No next Title</small>");
        }
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
            MPD::Song * current_song = data.get_song();
            if(current_song != NULL)
            {

                mp_TitleLabel->set_markup(current_song->song_format("<b>${title}</b> (Track ${track})")); 
                mp_ArtistAlbumLabel->set_markup(current_song->song_format("<small>by <b>${artist}</b> on <b>${album}</b> (${date})</small>")); 

            }
            else
            {
                mp_TitleLabel->set_markup("<b>Not Playing</b>"); 
                mp_ArtistAlbumLabel->set_markup("<small>Select a new Song</small>"); 
            }
        }

        if(event & (MPD_IDLE_PLAYER|MPD_IDLE_OPTIONS))
        {
            update_next_song_widget(data);
        }
    }
}
