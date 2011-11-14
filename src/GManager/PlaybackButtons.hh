#ifndef FREYA_PLAYBACKBUTTONS_GUARD
#define FREYA_PLAYBACKBUTTONS_GUARD

#include <gtkmm.h>
#include "../MPD/Client.hh"


namespace GManager
{
    class PlaybackButtons
    {
        public:

            PlaybackButtons(MPD::Client& client, const Glib::RefPtr<Gtk::Builder>& builder);
            ~PlaybackButtons();

        private:

            void on_button_stop(void);
            void on_button_play(void);
            void on_button_pause(void);
            void on_button_next(void);
            void on_button_prev(void);

            /* Widgets */
            Gtk::Button *stop_button, *play_button, *pause_button, *prev_button, *next_button;

            MPD::Client * mp_Client;
    };
}

#endif
