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
#include "NowPlaying.hh"
#include "../../Utils/Utils.hh"

namespace Browser
{
    NowPlaying::NowPlaying(MPD::Client& client, Glib::RefPtr<Gtk::Builder>& builder) :
        AbstractBrowser("Now Playing",
                true,  /* Needs connection? */
                true,  /* Is visible?       */
                Gtk::Stock::CDROM),
        AbstractClientUser(client)
    {
        BUILDER_ADD(builder,"ui/NowPlaying.glade");
        BUILDER_GET(builder,"np_scrollwindow",mp_NPScroll);

        ADD_MANAGER(builder,"np_coverart_expander",mp_CoverArt);
        ADD_MANAGER(builder,"np_textitems_expander",mp_Textitems);
        ADD_MANAGER(builder,"np_tracklist_expander",mp_Tracklist);
        ADD_MANAGER(builder,"np_otheralbums_expander",mp_OtherAlbums);
        ADD_MANAGER(builder,"np_artistimage_expander",mp_ArtistPhotos);
        ADD_MANAGER(builder,"np_relatedlinks_expander",mp_RelatedLinks);

        get_container()->show_all();
    }

    /////////////////////////////

    Gtk::Widget * NowPlaying::get_container()
    {
        return mp_NPScroll;        
    }

    /////////////////////////////
            
    void NowPlaying::on_client_update(mpd_idle events, MPD::NotifyData& data)
    {
        for(ManagerVector::iterator it = managerList.begin(); it != managerList.end(); it++) {
            (*it)->update(*mp_Client,events,data);
        }
    }
    
    /////////////////////////////

    void NowPlaying::on_connection_change(bool server_changed, bool is_connected)
    {

    }
}
