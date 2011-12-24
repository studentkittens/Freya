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

/**
 * @brief Test.
 */
namespace Browser
{
    /**
     * @brief A Baseclass for Widgets that want to implement easily popup widgets
     *
     * This class registers the needed signals and parses a UI Definition given by the derived class.
     * See QueuePopup, DatabasePopup or PlaylistManagerPopup for examples how this exactly works.
     */
    class BasePopup
    {
        public:

            /**
             * @brief 
             *
             * @param to_register The widget to register, for example a Gtk::TreeView
             * @param ui_definition The ui definition defining the Menu structure
             */
            BasePopup(Gtk::Widget * to_register, Glib::ustring& ui_definition);

            /**
             * @brief Get a signal proxy of a certain Gtk::Action in the menu
             *
             * @param name The name of the menu.
             *
             * @return a signal proxy, on which you can call connect()
             */
            Glib::SignalProxy0<void> get_action(const char * name);

        protected:

            /**
             * @brief This object stores the parsed UI Definition
             */
            Glib::RefPtr<Gtk::UIManager> m_refUIManager;
            /**
             * @brief All actions are added to this object
             */
            Glib::RefPtr<Gtk::ActionGroup> m_refActionGroup; 
            /**
             * @brief The actual definition
             */
            Glib::ustring * m_UiDefinition;
            /**
             * @brief The visible popup
             */
            Gtk::Menu * mp_Popup;

            /**
             * @brief Add an item to the Menu Popup
             *
             * @param action the action defined in the UI definition
             * @param item_name The name of the titem
             * @param item_label The visual name of the item
             * @param item_tooltip A tooltip, that is actually not shown
             * @param icon The icon shown lefthand to the label
             */
            void menu_add_item(Glib::RefPtr<Gtk::Action>& action,
                    Glib::ustring item_name,
                    Glib::ustring item_label,
                    Glib::ustring item_tooltip,
                    Gtk::StockID icon);

            /**
             * @brief Call this when done with adding actions
             */
            void menu_construct(Glib::ustring menu_name);

        private:
            /**
             * @brief Let the menu popup
             *
             * @param event 
             *
             * @return 
             */
            bool menu_popup(GdkEventButton * event);
    };
}

#endif /* end of include guard: FREYA_ABSTRACT_POPUP */
