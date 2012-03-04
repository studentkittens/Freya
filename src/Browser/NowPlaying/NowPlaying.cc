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
                Gtk::Stock::CDROM)
    {
        BUILDER_ADD(builder,"ui/NowPlaying.glade");
        BUILDER_GET(builder,"np_scrollwindow",mp_NPScroll);

        BUILDER_GET_DERIVED(builder,"np_coverart_expander",mp_CoverArt);
        BUILDER_GET_DERIVED(builder,"np_textitems_expander",mp_Textitems);
        BUILDER_GET_DERIVED(builder,"np_tracklist_expander",mp_Tracklist);
        BUILDER_GET_DERIVED(builder,"np_otheralbums_expander",mp_OtherAlbums);
        BUILDER_GET_DERIVED(builder,"np_artistimage_expander",mp_ArtistPhotos);
        BUILDER_GET_DERIVED(builder,"np_relatedlinks_expander",mp_RelatedLinks);

        get_container()->show_all();
    }

    /////////////////////////////

    Gtk::Widget * NowPlaying::get_container()
    {
        return mp_NPScroll;        
    }
    
    /////////////////////////////
}
