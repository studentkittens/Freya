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

            Gtk::Dialog * mp_Dialog;
            MPD::Client * mp_Client;
    };
}

#endif /* end of include guard: FREYA_PLAYLISTADD_DIALOG */
