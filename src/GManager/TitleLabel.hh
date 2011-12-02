#ifndef FREYA_TITLELABEL_GUARD
#define FREYA_TITLELABEL_GUARD

#include <gtkmm.h>
#include "../MPD/Client.hh"
#include "../AbstractClientUser.hh"

namespace GManager
{
    class TitleLabel : public AbstractClientUser
    {
        public:

            TitleLabel(MPD::Client& client, const Glib::RefPtr<Gtk::Builder>& builder);

        private:

            void on_client_update(enum mpd_idle, MPD::NotifyData& data);
            void on_connection_change(bool is_connected);
            void update_next_song_widget(MPD::NotifyData& data);

            /* Widgets */
            Gtk::Label * mp_TitleLabel, * mp_ArtistAlbumLabel, 
                       * mp_NextSongArtistLabel, * mp_NextSongTitleLabel;

            MPD::Client * mp_Client;
    };
}

#endif
