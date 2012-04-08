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
#ifndef FREYA_NOTIFY_MANAGER_GUARD
#define FREYA_NOTIFY_MANAGER_GUARD

#include "../MPD/AbstractClientUser.hh"
#include "../Notify/Notify.hh"

namespace GManager
{
/**
 * @brief Manages Notifications that are triggered on player events
 *
 * It does not offer any relevant public methods
 */
class NotifyManager : public MPD::AbstractClientUser
{
public:
    NotifyManager(MPD::Client& client);

private:

    void on_client_update(enum mpd_idle event, MPD::NotifyData& data);
    void on_connection_change(bool server_changed, bool is_connected);
};
}

#endif /* end of include guard: FREYA_NOTIFY_MANAGER_GUARD */
