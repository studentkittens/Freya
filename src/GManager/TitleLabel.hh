#ifndef FREYA_TITLELABEL_GUARD
#define FREYA_TITLELABEL_GUARD

#include <gtkmm.h>
#include "../MPD/Client.hh"

namespace GManager
{
    class TitleLabel
    {
        public:

            TitleLabel(MPD::Client& client, const Glib::RefPtr<Gtk::Builder>& builder);
            ~TitleLabel();

        private:

            void on_client_update(enum mpd_idle, MPD::NotifyData& data);
            void update_next_song_widget(MPD::NotifyData& data);

            /* Widgets */
            Gtk::Label * mp_TitleLabel, * mp_ArtistAlbumLabel, 
                       * mp_NextSongArtistLabel, * mp_NextSongTitleLabel;

            MPD::Client * mp_Client;
    };
}

#endif
