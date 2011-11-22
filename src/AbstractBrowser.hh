#ifndef FREYA_ABSTRACT_BROWSER
#define FREYA_ABSTRACT_BROWSER

#include <gtkmm.h>
#include <iostream>

/**
 * @brief Inherit from this class in order to be able to add the browser to the browserlist
 */
class AbstractBrowser
{
    public:

        AbstractBrowser(const char * name) : m_Name(name) {}

        /**
         * @brief Tell BrowserList which element to manage 
         *
         * You are supposed to override this.
         *
         * @return A reference to the containing widget of the browser 
         */
        virtual Gtk::Widget * get_container(void) = 0; /* No Impl. */ 
        
        /**
         * @brief Get the name of the browser (shown in the browserlist)
         *
         * Note: You do NOT need to override this.
         *
         * @return a reference to a ustring
         */
        Glib::ustring& get_name(void) { return m_Name; }

    private:

        Glib::ustring m_Name;
};

#endif
