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

#include "TextView.hh"

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
        BUILDER_GET(builder,"np_notebook",mp_NBook);

        BUILDER_GET(builder,"np_ArtistLabel",mp_ArtistLabel);
        BUILDER_GET(builder,"np_AlbumLabel", mp_AlbumLabel);
        BUILDER_GET(builder,"np_TitleLabel", mp_TitleLabel);
        BUILDER_GET(builder,"np_YearLabel",  mp_YearLabel);

        /* 
         * Type selector (lyrics, album review etc.)
         * Connect signals, and setup internal model
         */
        BUILDER_GET(builder,"np_TypeCombo", mp_TypeSelection);
        m_TypeModel = Gtk::ListStore::create(m_TypeColumns); 
        mp_TypeSelection->set_model(m_TypeModel);       

        /* Clear all previous renderers */
        mp_TypeSelection->clear();

        /* Add custom renderer for the icon */
        Gtk::CellRenderer * renderer = NULL;

        renderer = manage (new Gtk::CellRendererPixbuf); 
        mp_TypeSelection->pack_start(*renderer,false);
        mp_TypeSelection->add_attribute(*renderer,"pixbuf",1);

        renderer = manage (new Gtk::CellRendererText); 
        mp_TypeSelection->pack_start(*renderer,true);
        mp_TypeSelection->add_attribute(*renderer,"text",0);
        
        mp_TypeSelection->signal_changed().connect(sigc::mem_fun(*this,
                    &NowPlaying::on_type_combo_changed));

        BUILDER_GET_DERIVED(builder,"np_CoverEventBox",mp_Cover);

        setup(builder);
    }

    /////////////////////////////

    Gtk::Widget * NowPlaying::get_container()
    {
        return mp_NPScroll;        
    }
    
    /////////////////////////////
    ///////// Private ///////////
    /////////////////////////////
    
    void NowPlaying::add_txtview_page(Glib::RefPtr<Gtk::Builder>& builder,const char * name,Gtk::StockID icon)
    {
        Glib::RefPtr<Gtk::Builder> temp_builder = Gtk::Builder::create_from_file("ui/NowPlaying_TextView.glade");
        if(temp_builder) {
            TextView * pageView = NULL;
            BUILDER_GET_DERIVED(temp_builder,"np_textview_scw",pageView);
            if(pageView != NULL) {
                Gtk::TreeModel::Row row = *(m_TypeModel->append());
                row[m_TypeColumns.m_col_id]   = name; 
                row[m_TypeColumns.m_col_icon] = mp_NBook->render_icon_pixbuf(icon,Gtk::ICON_SIZE_DND);
                mp_NBook->append_page(*pageView,name);
            } else {
                Error("Broken .glade file");
            }
        } else {
            Error("Cannot instantiate temporate builder");
            Error("Does NowPlaying_TextView.glade exist?");
        }
    }

    /////////////////////////////
   
    /* 
     * When selecting a type in the Combobox, jump to 
     * the specified field in the notebook
     * (this is a little crude)
     */ 
    void NowPlaying::on_type_combo_changed()
    {
       mp_NBook->set_current_page(mp_TypeSelection->get_active_row_number()); 
    }
    
    /////////////////////////////

    /*
     * Setup basic properties of the page
     */
    void NowPlaying::setup(Glib::RefPtr<Gtk::Builder>& builder) 
    {
        add_txtview_page(builder,"Songtext",Gtk::Stock::FILE);
        add_txtview_page(builder,"Artist Biography",Gtk::Stock::ORIENTATION_PORTRAIT);
        add_txtview_page(builder,"Album Review",Gtk::Stock::CDROM);
        mp_TypeSelection->set_active(0);

        // Colors
        Gdk::RGBA black;
        black.set_rgba(0,0,0);

        // Just to be sure
        Gtk::Viewport * vp = NULL;
        BUILDER_GET(builder,"np_Viewport",vp);
        vp->override_background_color(black);

        get_container()->show_all();
    }

    /////////////////////////////
       
    void NowPlaying::on_client_update(mpd_idle events, MPD::NotifyData& data)
    {
        if(events & MPD_IDLE_PLAYER) {
            MPD::Song * curr = data.get_song();
            if(curr != NULL) {
                mp_ArtistLabel->set_text(curr->get_tag(MPD_TAG_ARTIST,0));
                mp_AlbumLabel ->set_text(curr->get_tag(MPD_TAG_ALBUM,0));
                mp_TitleLabel ->set_text(curr->get_tag(MPD_TAG_TITLE,0));
                mp_YearLabel  ->set_text(curr->get_tag(MPD_TAG_DATE,0));
            } else {
                mp_ArtistLabel->set_text("[Not Playing]");
                mp_AlbumLabel ->set_text("");
                mp_TitleLabel ->set_text("");
                mp_YearLabel  ->set_text("");
            }
        }
    }
}
