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
#ifndef FREYA_QUEUE_POPUP_GUARD
#define FREYA_QUEUE_POPUP_GUARD

#include "../BasePopup.hh"
#include <gtkmm.h>

namespace Browser
{
    /**
     * @brief The Popup for Browser::Queue
     *
     * See Browser::BasePopup for a more detailed description.
     */
    class QueuePopup : public BasePopup
    {
    public:
        QueuePopup(Gtk::Widget& to_register);

    private:
        Glib::RefPtr<Gtk::Action> m_ActionDel;
        Glib::RefPtr<Gtk::Action> m_ActionPlAdd;
        Glib::RefPtr<Gtk::Action> m_ActionClear;
    };
}
#endif /* end of include guard: FREYA_QUEUE_POPUP_GUARD */
