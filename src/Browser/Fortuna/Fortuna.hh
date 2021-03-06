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
#ifndef FREYA_FORTUNA_GUARD
#define FREYA_FORTUNA_GUARD

#include "../AbstractBrowser.hh"
#include <gtkmm.h>

namespace Browser
{
/**
 * @brief A little easteregg browser
 *
 * Shows a kittenhead and a speechbubble which shows a random fortune,
 * that is read from the 'fortune' utility. If fortune does not seem to be
 * installed the predefined glade string is not modified.
 *
 * Usually this browser only shown on startup, else it's hidden.
 */
class Fortuna : public AbstractBrowser
{
public:

    /**
     * @brief Builds itself once being passed a builder reference
     *
     * @param builder
     */
    Fortuna(Glib::RefPtr<Gtk::Builder>& builder,GManager::BrowserList& list);

    /**
     * @brief Implemented by AbstractBrowser
     *
     * @return
     */
    Gtk::Widget * get_container();

private:

    /* Workers */
    Glib::ustring get_fortune();
    void on_refresh_fortune();

    /* Widgets */
    Gtk::ScrolledWindow * mp_FortuneScroll;
    Gtk::Label * mp_FortuneLabel;
    Gtk::Button * mp_FortuneRefresh;
};
}


#endif /* end of include guard: FREYA_FORTUNA_GUARD */
