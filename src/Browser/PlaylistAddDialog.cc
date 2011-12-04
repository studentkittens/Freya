#include "PlaylistAddDialog.hh"
#include "../Utils/Utils.hh"

namespace Browser
{
    PlaylistAddDialog::PlaylistAddDialog(MPD::Client& client, Glib::RefPtr<Gtk::Builder> builder) :
        is_running(false),
        mp_Dialog(NULL)
    {
        mp_Client = &client;
        BUILDER_ADD(builder,"ui/PlaylistAddDialog.glade");
        BUILDER_GET_NO_MANAGE(builder,"playlist_add_dialog",mp_Dialog);

        Gtk::Button * button_cancel, * button_add;
        BUILDER_GET(builder,"playlist_cancel",button_cancel);
        BUILDER_GET(builder,"playlist_add",button_add);

        button_cancel->signal_clicked().connect(
                sigc::mem_fun(*this,&PlaylistAddDialog::on_cancel_clicked));
        button_add->signal_clicked().connect(
                sigc::mem_fun(*this,&PlaylistAddDialog::on_add_clicked));
    }

    /* ----------------------- */
    
    PlaylistAddDialog::~PlaylistAddDialog(void)
    {
        delete mp_Dialog;
    }
    
    /* ----------------------- */

    void PlaylistAddDialog::on_add_clicked(void)
    {
        // TODO: Add The Playlist here.. //
        on_cancel_clicked();
    }

    /* ----------------------- */
    
    void PlaylistAddDialog::on_cancel_clicked(void)
    {
        mp_Dialog->hide();
        is_running = false;
    }
    
    /* ----------------------- */

    void PlaylistAddDialog::run(void)
    {
        if(is_running == false)
        {
            is_running = true;
            mp_Dialog->show();
        }
    }
}
