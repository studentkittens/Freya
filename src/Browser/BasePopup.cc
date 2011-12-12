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
#include "BasePopup.hh"

namespace Browser
{
    BasePopup::BasePopup(Gtk::Widget * to_register, Glib::ustring& ui_definition)
    {
        if(to_register != NULL)
        {
            /* Connect to rightclick event */
            to_register->signal_button_press_event().connect(sigc::mem_fun(*this,&BasePopup::menu_popup),false);
        }

        m_UiDefinition = &ui_definition;
        m_refUIManager = Gtk::UIManager::create();
        m_refActionGroup = Gtk::ActionGroup::create();
        mp_Popup = NULL;
    }

    /*-------------------------------*/

    bool BasePopup::menu_popup(GdkEventButton * event)
    {
        g_assert(event);
        if(event->type == GDK_BUTTON_PRESS && event->button == 3)
        {
            mp_Popup->popup(event->button,event->time);
        }
        return false;
    }
    
    /*-------------------------------*/

    Glib::SignalProxy0<void> BasePopup::get_action(const char * name)
    {
        Glib::RefPtr<Gtk::Action> action = m_refActionGroup->get_action(name);
        return action->signal_activate();
    }

    /*-------------------------------*/

    /**
     * @brief Call this to add the actual action
     *
     * @param action A refpointer to a Gtk::Action
     * @param item_name item name in the definiton
     * @param item_label 
     * @param item_tooltip
     * @param icon
     */
    void BasePopup::menu_add_item(Glib::RefPtr<Gtk::Action>& action,
            Glib::ustring item_name,
            Glib::ustring item_label,
            Glib::ustring item_tooltip,
            Gtk::StockID icon)
    {
        action = Gtk::Action::create(item_name,icon,item_label,item_tooltip);
        m_refActionGroup->add(action);
    }

    /*-------------------------------*/

    /**
     * @brief Call this when done with adding actions
     *        Convention: Menu must be called "PopMenu" in def.
     */
    void BasePopup::menu_construct(Glib::ustring menu_name)
    {
        /* Set up the menu with all actions inside */
        m_refUIManager->insert_action_group(m_refActionGroup);
        m_refUIManager->add_ui_from_string(*m_UiDefinition);
        mp_Popup = (Gtk::Menu*)(m_refUIManager->get_widget("/" + menu_name));
    }

    /*-------------------------------*/
}
