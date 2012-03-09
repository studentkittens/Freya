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
#include "VolumeSlider.hh"
#include "../Utils/Utils.hh"
#include "../Notify/Notify.hh"

#define LINE_GAP   1 // px
#define LINE_WIDTH 2 // px

namespace GManager
{
    VolumeSlider::VolumeSlider(MPD::Client& client, const Glib::RefPtr<Gtk::Builder>& builder) :
        AbstractClientUser(client)
    {
        Gtk::Alignment * align = NULL;
        BUILDER_GET(builder,"volumeslider_align",align);
        set_size_request(75);
        align->add(*this);
        align->show_all();

    }

    /////////////////////////

    void VolumeSlider::on_client_update(enum mpd_idle event, MPD::NotifyData& data)
    {
        // TODO: Does not get drawn correctly on startup,
        //       because, the widget has a width of 0 at
        //       this point
        if(event & (MPD_IDLE_MIXER))
        {
            set_percentage(data.get_status().get_volume());
        }
    }

    /////////////////////////

    /* 
     * Does the acutal drawing work, simple gap based layout,
     * always going from left down, to upper right corner
     */
    bool VolumeSlider::on_draw(const Cairo::RefPtr<Cairo::Context>& cr)
    {
        Gtk::Allocation allocation = get_allocation();
        const int width = allocation.get_width();
        const int height = allocation.get_height();
        const int extra_gap = LINE_WIDTH + LINE_GAP;
        bool turnedColor = false;

        const double pitch = height / (double)width;

        Gdk::RGBA& ac = get_active_color();
        Gdk::RGBA& ic = get_inactive_color();

        cr->set_line_width(LINE_WIDTH);
        cr->set_source_rgb(ac.get_red(), ac.get_green(), ac.get_blue());

        for(int i = 0; i < width; i += extra_gap) {
            cr->move_to(i,height);

            double lim = height - (i * pitch) - 2;
            cr->line_to(i,lim);

            if(lim <= 0) {
                break;
            }

            if(!turnedColor && i >= get_border()) {
                cr->stroke();
                cr->set_source_rgb(ic.get_red(), ic.get_green(), ic.get_blue());
                turnedColor = !turnedColor;
            }
        }

        cr->stroke();
        return true;
    }

    /////////////////////////

    void VolumeSlider::on_percent_change()
    {
        mp_Client->set_volume(get_percentage());
    }   
    
    /////////////////////////
    
    void VolumeSlider::on_connection_change(bool server_changed, bool is_connected) {}
}
