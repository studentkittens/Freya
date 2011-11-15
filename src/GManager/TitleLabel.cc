#include "TitleLabel.hh"

namespace GManager
{
    TitleLabel::TitleLabel(MPD::Client& client, const Glib::RefPtr<Gtk::Builder>& builder)
    {
        try
        {
            mp_Client = &client;
            mp_Client->get_notify().connect(sigc::mem_fun(*this,&TitleLabel::on_client_update));

            builder->get_widget("title_label",mp_TitleLabel);
            builder->get_widget("artist_album_label",mp_ArtistAlbumLabel);
            Gtk::manage(mp_TitleLabel);
            Gtk::manage(mp_ArtistAlbumLabel);
        }
        catch(const Gtk::BuilderError& e)
        {
            Error("BuilderError: %s",e.what().c_str());
        }
    }

    TitleLabel::~TitleLabel() {}

    void TitleLabel::on_client_update(enum mpd_idle, MPD::NotifyData& data)
    {
        MPD::Song& current_song = data.get_song();
        char * title_string = g_markup_printf_escaped("<b>%s</b>",current_song.get_tag(MPD_TAG_TITLE,0));
        char * artist_album = g_markup_printf_escaped("by %s on %s",
                                              current_song.get_tag(MPD_TAG_ARTIST,0),
                                              current_song.get_tag(MPD_TAG_ALBUM,0));
          
        mp_TitleLabel->set_markup_with_mnemonic(title_string); 
        mp_ArtistAlbumLabel->set_markup_with_mnemonic(artist_album); 
        g_free(artist_album);
        g_free(title_string);
    }
}
