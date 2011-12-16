 /***********************************************************
* This file is part of Freya 
* - A free MPD Gtk3 MPD Client -
* 
* Authors: Christopher Pahl, Christoph Piechula,
*          Eduard Schneider, Marc Tigges
*
* Copyright (C) [2011-2012]
* Hosted at: https://github.com/studentkittens/Freya
*
*              __..--''``---....___   _..._    __
*    /// //_.-'    .-/";  `        ``<._  ``.''_ `. / // /
*   ///_.-' _..--.'_                        `( ) ) // //
*   / (_..-' // (< _     ;_..__               ; `' / ///
*    / // // //  `-._,_)' // / ``--...____..-' /// / //  
*  Ascii-Art by Felix Lee <flee@cse.psu.edu>
*
* Freya is free software: you can redistribute it and/or modify
* it under the terms of the GNU General Public License as published by
* the Free Software Foundation, either version 3 of the License, or
* (at your option) any later version.
*
* Freya is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
* GNU General Public License for more details.
*
* You should have received a copy of the GNU General Public License
* along with Freya. If not, see <http://www.gnu.org/licenses/>.
**************************************************************/
#include "PlaylistAddDialog.hh"
#include "../Utils/Utils.hh"

namespace Browser
{
    PlaylistAddDialog::PlaylistAddDialog(MPD::Client& client, Glib::RefPtr<Gtk::Builder> builder) :
        AbstractClientUser(client),
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
        mp_Client->playlist_save(new_pl_name.c_str()); 
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
    
    /* ----------------------- */
            
    void PlaylistAddDialog::on_client_update(mpd_idle event, MPD::NotifyData& data)
    {}
    
    /* ----------------------- */

    void PlaylistAddDialog::on_connection_change(bool is_connected)
    {}
}
