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

        BUILDER_GET(builder,"playlist_cancel",mp_CancelButton);
        BUILDER_GET(builder,"playlist_add",mp_ApplyButton);
        BUILDER_GET(builder,"playlist_name_entry",mp_PlaylistEntry);

        mp_CancelButton->signal_clicked().connect(
                sigc::mem_fun(*this,&PlaylistAddDialog::on_cancel_clicked));
        mp_ApplyButton->signal_clicked().connect(
                sigc::mem_fun(*this,&PlaylistAddDialog::on_add_clicked));
        mp_PlaylistEntry->signal_changed().connect(
                sigc::mem_fun(*this,&PlaylistAddDialog::on_entry_change));
        mp_PlaylistEntry->signal_activate().connect(
                sigc::mem_fun(*this,&PlaylistAddDialog::on_entry_activate));

    }

    /* ----------------------- */
    
    PlaylistAddDialog::~PlaylistAddDialog(void)
    {
        delete mp_Dialog;
    }
    
    /* ----------------------- */

    void PlaylistAddDialog::on_add_clicked(void)
    {
        Glib::ustring new_pl_name = mp_PlaylistEntry->get_text();
        g_printerr("Creating new playlist: %s\n",new_pl_name.c_str());

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
    
    /* ----------------------- */

    void PlaylistAddDialog::on_entry_change(void)
    {
        /* Get length of Text */
        mp_ApplyButton->set_sensitive(mp_PlaylistEntry->get_text_length() > 0);
    }
    
    /* ----------------------- */

    void PlaylistAddDialog::on_entry_activate(void)
    {
        on_add_clicked();
    }
}
