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

    /**
     * @brief Inherit from this class to be able to add this browser to the browserlist
     *
     * @param name The name shown in the list
     * @param is_visible if it is visible in the list (most likely true)
     * @param needs_connection false if this browser works withouth a connection
     * @param icon the icon shown lefthand to the name
     */
    AbstractBrowser(const char * name,
                    bool is_visible,
                    bool needs_connection,
                    Gtk::StockID icon)
        : m_Name(name),
          m_IconId(icon),
          m_NeedsConnection(needs_connection),
          m_IsVisible(is_visible)
    {}

    /**
     * @brief Tell BrowserList which element to manage
     *
     * You are supposed to override this.
     *
     * @return A reference to the containing widget of the browser
     */
    virtual Gtk::Widget * get_container() = 0; /* No Impl. */

    /**
     * @brief Get the name of the browser (shown in the browserlist)
     *
     * Note: You do NOT need to override this.
     *
     * @return a reference to a ustring
     */
    Glib::ustring& get_name()
    {
        return m_Name;
    }

    /**
     * @brief Returns the set icon for this browser
     *
     * @return See above.
     */
    Gtk::StockID get_icon_stock_id()
    {
        return m_IconId;
    }

    /**
     * @brief Tells if browser is visible in browserlist
     *
     * @return a boolean
     */
    bool is_visible()
    {
        return m_IsVisible;
    }

    /**
     * @brief If this browser works without a connection (if false)
     *
     * @return a boolean
     */
    bool needs_connection()
    {
        return m_NeedsConnection;
    }

private:

    Glib::ustring m_Name;
    Gtk::StockID m_IconId;
    bool m_NeedsConnection;
    bool m_IsVisible;
};

#endif
