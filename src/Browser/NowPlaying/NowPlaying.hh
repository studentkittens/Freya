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
#ifndef FREYA_NOWPLAYING_GUARD
#define FREYA_NOWPLAYING_GUARD

#include "../../MPD/Client.hh"
#include "../AbstractBrowser.hh"
#include <gtkmm.h>

#include "OtherAlbumsMgr.hh"
#include "TracklistMgr.hh"
#include "TextItemsMgr.hh"
#include "CoverArtMgr.hh"
#include "ArtistPhotosMgr.hh"
#include "RelatedLinksMgr.hh"
#include "../../Glyr/UpdateInterface.hh"

namespace Browser
{
    class NowPlaying : public AbstractBrowser, public MPD::AbstractClientUser
    {
        public:

            /**
             * @brief Builds itself once being passed a builder reference
             *
             * @param builder
             */
            NowPlaying(MPD::Client &client, Glib::RefPtr<Gtk::Builder>& builder);

            /**
             * @brief Implemented by AbstractBrowser
             *
             * @return
             */
            Gtk::Widget * get_container();

        private:

            // Client

            void on_client_update(mpd_idle, MPD::NotifyData&);
            void on_connection_change(bool, bool);
    
            void on_expander_changed(Glyr::UpdateInterface * intf);

            // Vars

            ManagerVector managerList;
            Gtk::ScrolledWindow * mp_NPScroll;
            MPD::NotifyData * lastData;

            // Managers

            ArtistPhotosMgr  * mp_ArtistPhotos;
            RelatedLinksMgr * mp_RelatedLinks;
            OtherAlbumsMgr * mp_OtherAlbums;
            TracklistMgr  * mp_Tracklist;
            TextItemsMgr * mp_Textitems;
            CoverArtMgr * mp_CoverArt;
    };
}


#endif /* end of include guard: FREYA_NPLAYING_GUARD */
