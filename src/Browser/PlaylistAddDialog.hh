#ifndef FREYA_PLAYLISTADD_DIALOG
#define FREYA_PLAYLISTADD_DIALOG

#include "../MPD/Client.hh"
#include <gtkmm.h>

namespace Browser
{
    class PlaylistAddDialog 
    {
        public:
            PlaylistAddDialog(MPD::Client& client, Glib::RefPtr<Gtk::Builder> builder);
            ~PlaylistAddDialog(void);
            void run(void);

        private:

            void on_cancel_clicked(void);
            void on_add_clicked(void);
            void on_entry_change(void);
            void on_entry_activate(void);

            bool is_running;
            Gtk::Dialog * mp_Dialog;
            MPD::Client * mp_Client;

            Gtk::Entry * mp_PlaylistEntry;
            Gtk::Button * mp_ApplyButton, * mp_CancelButton; 
    };
}

#endif /* end of include guard: FREYA_PLAYLISTADD_DIALOG */
