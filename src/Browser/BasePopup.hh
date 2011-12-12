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
#ifndef FREYA_ABSTRACT_POPUP
#define FREYA_ABSTRACT_POPUP

#include <gtkmm.h>

namespace Browser
{
    class BasePopup
    {
        public:

            BasePopup(Gtk::Widget * to_register, Glib::ustring& ui_definition);
            bool menu_popup(GdkEventButton * event);

            /**
             * @brief Get a signal proxy of a certain Gtk::Action in the menu
             *
             * @param name The name of the menu.
             *
             * @return a signal proxy, on which you can call connect()
             */
            Glib::SignalProxy0<void> get_action(const char * name);

        protected:

            Glib::RefPtr<Gtk::UIManager> m_refUIManager;
            Glib::RefPtr<Gtk::ActionGroup> m_refActionGroup; 
            Glib::ustring * m_UiDefinition;
            Gtk::Menu * mp_Popup;

            void menu_add_item(Glib::RefPtr<Gtk::Action>& action,
                    Glib::ustring item_name,
                    Glib::ustring item_label,
                    Glib::ustring item_tooltip,
                    Gtk::StockID icon);

            /**
             * @brief Call this when done with adding actions
             *        Convention: Menu must be called "PopMenu" in def.
             */
            void menu_construct(Glib::ustring menu_name);
    };
}

#endif /* end of include guard: FREYA_ABSTRACT_POPUP */
