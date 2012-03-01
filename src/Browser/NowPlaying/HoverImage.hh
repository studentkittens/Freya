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

#ifndef FREYA_HOVERIMAGE_GUARD
#define FREYA_HOVERIMAGE_GUARD

#include <gtkmm.h>

namespace Browser
{
    /* 
     * A Gtk::Builder derived class,
     * implementing a Hoverable Image,
     * i.e. an image with a certain dimension, that shows
     * the full-sized version after a click
     */
    class HoverImage : public Gtk::EventBox 
    {
        public:
            HoverImage(BaseObjectType* cobject, const Glib::RefPtr<Gtk::Builder>& builder);
            HoverImage();

        private:
           // Normal:
           void setup();

            // Signals:
           bool on_image_clicked(GdkEventButton * ev);

           // Vars:
           Gtk::Image * mImg;
           Glib::RefPtr<Gdk::Pixbuf> mNoImage;
    }; 
}

#endif /* end of include guard: FREYA_HOVERIMAGE_GUARD */

