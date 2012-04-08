/***********************************************************
* This file is part of Freya
* - A free MPD Gtk3 MPD Client -
*
* Authors: Christopher Pahl, Christoph Piechula,
*          Eduard Schneider
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
#ifndef FREYA_PLAYLISTADD_DIALOG
#define FREYA_PLAYLISTADD_DIALOG

#include "../../MPD/Client.hh"
#include "../../MPD/AbstractClientUser.hh"

#include <gtkmm.h>

namespace Browser
{
/**
 * @brief Shows a simple dialog when a new playlist needs to be saved
 *
 * This class does the adding itself
 */
class PlaylistAddDialog : public MPD::AbstractClientUser
{
public:
    PlaylistAddDialog(MPD::Client& client, Glib::RefPtr<Gtk::Builder> builder);
    ~PlaylistAddDialog();

    /**
     * @brief Show the dialog (closes itself)
     *
     * This functions blocks, other items in Freya may not be accessed anymore
     */
    void run();

private:

    void on_cancel_clicked();
    void on_add_clicked();
    void on_entry_change();
    void on_entry_activate();

    /* From AbstractClientUser */
    void on_client_update(mpd_idle event, MPD::NotifyData& data);
    void on_connection_change(bool server_changed, bool is_connected);

    bool is_running;
    Gtk::Dialog * mp_Dialog;
    Gtk::Entry * mp_PlaylistEntry;
    Gtk::Button * mp_ApplyButton, * mp_CancelButton;
};
}

#endif /* end of include guard: FREYA_PLAYLISTADD_DIALOG */
