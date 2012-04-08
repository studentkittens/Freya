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
NowPlaying::NowPlaying(MPD::Client& client, Glib::RefPtr<Gtk::Builder>& builder,GManager::BrowserList& list) :
    AbstractBrowser(list,
                    "Now Playing",
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
    /*
     * Register for the 'expand' signal of all Managers,
     * so we can send an update signal once they get visible
     */
    for(ManagerVector::iterator it = managerList.begin(); it != managerList.end(); it++)
    {
        Gtk::Expander * ex = dynamic_cast<Gtk::Expander*>(*it);
        if(ex != NULL)
        {
            ex->property_expanded().signal_changed().connect(
                sigc::bind(sigc::mem_fun(*this,&NowPlaying::on_expander_changed),*it)
            );
        }
    }
    // Colors
    Gdk::RGBA black;
    black.set_rgba(0,0,0);
    Gtk::Viewport * vp = NULL;
    BUILDER_GET(builder,"np_Viewport",vp);
    vp->override_background_color(black);
    get_container()->show_all();
}

/////////////////////////////

void NowPlaying::on_expander_changed(Glyr::UpdateInterface * intf)
{
    if(lastData != NULL)
    {
        Gtk::Expander * ex = dynamic_cast<Gtk::Expander*>(intf);
        if(ex && ex->get_expanded())
        {
            intf->update(*mp_Client,MPD_IDLE_PLAYER,*lastData);
        }
    }
}

/////////////////////////////

void NowPlaying::on_getting_active()
{
    if(lastData != NULL)
    {
        on_client_update(MPD_IDLE_PLAYER,*lastData);
    }
}

/////////////////////////////

Gtk::Widget * NowPlaying::get_container()
{
    return mp_NPScroll;
}

/////////////////////////////

void NowPlaying::on_client_update(mpd_idle events, MPD::NotifyData& data)
{
    if((events & MPD_IDLE_PLAYER) && is_active())
    {
        for(ManagerVector::iterator it = managerList.begin(); it != managerList.end(); it++)
        {
            Gtk::Expander * ex = dynamic_cast<Gtk::Expander*>(*it);
            if(ex && ex->get_expanded())
            {
                (*it)->update(*mp_Client,events,data);
            }
        }
    }
    lastData = &data;
}

/////////////////////////////

void NowPlaying::on_connection_change(bool server_changed, bool is_connected)
{}
}
