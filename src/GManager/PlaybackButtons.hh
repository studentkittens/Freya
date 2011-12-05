#ifndef FREYA_PLAYBACKBUTTONS_GUARD
#define FREYA_PLAYBACKBUTTONS_GUARD

#include <gtkmm.h>
#include "../MPD/Client.hh"
#include "../AbstractClientUser.hh"

namespace GManager
{
    class PlaybackButtons : public AbstractClientUser
    {
        public:
            PlaybackButtons(MPD::Client& client, const Glib::RefPtr<Gtk::Builder>& builder);

        private:
            /* Client Signals */
            void on_client_update(enum mpd_idle event, MPD::NotifyData& data);
            void on_connection_change(bool is_connected);

            /* GTK Signals */
            void on_button_stop(void);
            void on_button_pause(void);
            void on_button_next(void);
            void on_button_prev(void);

            /* Widgets */
            Gtk::Button *stop_button, *pause_button, *prev_button, *next_button;
            Gtk::Image play_icon, pause_icon;
    };
}

#endif
