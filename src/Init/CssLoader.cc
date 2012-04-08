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

#include <gtkmm/cssprovider.h>
#include <gtkmm/stylecontext.h>

#include "Path.hh"
#include "defaultcss.inl"
#include "CssLoader.hh"

#include "../Log/Writer.hh"

namespace Init
{
CssLoader::CssLoader()
{
    Init::Path cfg;
    Glib::ustring cssPath = cfg.path_to_css();
    Glib::RefPtr<Gtk::CssProvider> cssProv = Gtk::CssProvider::create();
    Glib::RefPtr<Gtk::StyleContext> ctx = Gtk::StyleContext::create();
    try
    {
        cssProv->load_from_path(cssPath);
    }
    catch(...)
    {
        /*
         * Try to write a default css file
         * to the location, which resembles
         * the default css.
         * It will be read on the next start
         */
        FILE * overlay = fopen(cssPath.c_str(),"w");
        if(overlay != NULL)
        {
            Info("Wrote default css-style to %s",cssPath.c_str());
            fprintf(overlay,Init::defaultcss_inl.c_str());
            fclose(overlay);
        }
        else
        {
            Warning("No css-style loaded from %s",cssPath.c_str());
        }
        /*
         * Load from the defaultcss
         * string data for now.
         *
         * Retry on next start
         */
        cssProv->load_from_data(Init::defaultcss_inl);
    }
    ctx->add_provider_for_screen(Gdk::Screen::get_default(),cssProv,INT_MAX);
}
}
