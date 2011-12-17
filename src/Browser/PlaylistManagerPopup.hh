 /***********************************************************
* This file is part of Freya 
* - A free MPD Gtk3 MPD Client -
* 
* Authors: Christopher Pahl, Christoph Piechula,
*          Eduard Schneider, Marc Tigges
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
#ifndef FREYA_PLMANAGER_POPUP_GUARD
#define FREYA_PLMANAGER_POPUP_GUARD

#include <gtkmm.h>
#include "BasePopup.hh"

namespace Browser
{
    class PlaylistManagerPopup : public BasePopup 
    {
        public:
            PlaylistManagerPopup(Gtk::Widget& to_register);

        private:
            Glib::RefPtr<Gtk::Action> m_ActionAdd;
            Glib::RefPtr<Gtk::Action> m_ActionDel;
            Glib::RefPtr<Gtk::Action> m_ActionRepl;
    };
}
#endif 
