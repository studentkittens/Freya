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
            return true;
        }
        return false;
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
