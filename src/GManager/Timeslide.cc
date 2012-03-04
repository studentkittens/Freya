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
#include "Timeslide.hh"
#include "../Log/Writer.hh"
#include "../Utils/Utils.hh"

namespace GManager
{
    Timeslide::Timeslide(Heartbeat& tproxy, MPD::Client& client, const Glib::RefPtr<Gtk::Builder>& builder) :
        AbstractClientUser(client),
        mp_Heartbeat(&tproxy),
        currSong(NULL),
        drawFullLine(true)
    {
        Gtk::Alignment * align = NULL;
        BUILDER_GET(builder,"timeslider_align",align);
        set_size_request(75,12);
        align->add(*this);
        align->show_all();

        tproxy.signal_client_update().connect(sigc::mem_fun(*this,&Timeslide::tick));
    }

    //////////////////////////////

    void Timeslide::tick(double time)
    {
        if(currSong) {
            set_percentage(time / (double)currSong->get_duration() * 100.0);
        }
    }

    /* ------------------ */

    void Timeslide::on_connection_change(bool server_changed, bool is_connected)
    {
        if(is_connected == false) {
            drawFullLine = false;
        }
    }

    //////////////////////////////

    void Timeslide::on_client_update(enum mpd_idle event, MPD::NotifyData& data)
    {
        currSong = data.get_song();
        if(event & MPD_IDLE_PLAYER) {
            drawFullLine = (data.get_status().get_state() > (MPD_STATE_STOP));
            tick(data.get_status().get_elapsed_time());
        }
    }

    //////////////////////////////

    bool Timeslide::on_draw(const Cairo::RefPtr<Cairo::Context>& cr)
    {
        Gtk::Allocation allocation = get_allocation();
        const int width = allocation.get_width();
        const int height = allocation.get_height();
        const int line_width = 2; /* for the shell only */

        const int thick   = line_width + 2, /* px, border to window */
              thickd2 = (thick  >> 1),
              radius  = (height >> 1) - thickd2,
              mid     = (thick  >> 1) + radius,
              midx2   = (mid    << 1),
              length  = width - midx2;

        bool do_draw = drawFullLine;

        Gdk::RGBA& ac = get_active_color();
        Gdk::RGBA& ic = get_inactive_color();

        cr->set_line_cap(Cairo::LINE_CAP_SQUARE);
        cr->set_source_rgb(ac.get_red(),ac.get_green(),ac.get_blue());

        // Left Arc
        cr->set_line_width(line_width);
        cr->arc_negative(mid,mid,radius,-M_PI / 2, M_PI / 2);

        // Upper line
        cr->move_to(mid,thickd2);
        cr->line_to(mid + length, thickd2);

        // Right Arc
        cr->arc(mid + length, mid, radius, -M_PI / 2, M_PI / 2);

        // Lower line
        cr->move_to(mid, midx2 - thickd2);
        cr->line_to(mid + length, midx2 - thickd2);

        if(do_draw) {
            cr->rectangle(mid,thickd2,length,midx2 - 2*thickd2);
            cr->clip();
            cr->paint();
        } else {
            cr->stroke();
        }

        if(do_draw) {
            cr->set_source_rgb(ac.get_red(),ac.get_green(),ac.get_blue());
            cr->rectangle(0,0,get_border(),height);
            cr->fill();
            cr->set_source_rgb(ic.get_red(),ic.get_green(),ic.get_blue());
            cr->rectangle(get_border(),0,width - get_border(),height);
            cr->fill();
            cr->stroke();
        }

        return true;
    }

    //////////////////////////////

    /*
     * Called on userinput,
     * not when using set_percentage()
     */
    void Timeslide::on_percent_change()
    {
        if(currSong) {
            mp_Client->playback_seek(currSong->get_id(), round(get_percentage()/100.0 * currSong->get_duration()));
        }
    }
}
