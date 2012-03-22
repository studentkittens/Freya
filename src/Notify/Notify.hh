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
#ifndef FREYA_NOTIFY_GUARD
#define FREYA_NOTIFY_GUARD

#include "../Utils/Singleton.hh"

#include <gtkmm.h>
#include <libnotify/notify.h>

namespace Notify
{
    /**
     * @brief A Singletonclass to provide Access to libnotify, use the macros down preferrably
     */
    class Notify
    {
        DEF_SINGLETON( Notify )

        public:
            /**
             * @brief Calls libnotifys notify-send indirectly.
             *
             * @param hl The headline of the Notification-Popup.
             * @param msg Actual text to display.
             */
            void send_big(Glib::ustring hl, Glib::ustring msg);

            /**
             * @brief Equivalent to send_big() but with an Imageicon
             *
             * @param hl The headline of the Notification-Popup.
             * @param msg Actual text to display.
             * @param pixbuf GdkPixbuf-Pointer to the Image in Memory
             */
            void send_full(Glib::ustring hl, Glib::ustring msg, GdkPixbuf * pixbuf);

            /**
             * @brief Sets the Image to be displayed in the next Notification to a Stock-Icon
             *
             * This method is not threadsafe. If you need a threadsafe version see set_next_extra() on how to create a thread safe version
             *
             * @param stock Stock icon name. <a href="http://standards.freedesktop.org/icon-naming-spec/icon-naming-spec-latest.html">Examples</a>
             */
            void set_stock_icon(const char* stock);

            /**
             * @brief Detaches the next Notifcation, causing it to be displayed seperately rather than replacing the default Notification.
             *
             * The next Notification can't be altered in anyway from within the calling application for now. Also this method is NOT threadsafe.
             * If you need a threadsafe version, just write yourself a wrapper method that first aquires a mutex and then calls set_next_extra() AND a send-method.
             * Then ONLY use your thread safe wrapper to call this method.
             */
            void set_next_extra();

        private:
            Glib::ustring icon_name;
            int timeout,use_notify;
            bool extra;

            void do_init();
            void _send(const char *hl, const char *msg, const char * icon);
    };
}

#define NOTIFY_SEND(x,y) Notify::Notify::instance().send_big(x,y)    //x=headline, y=message
#define NOTIFY_SEND_FULL(x,y,z) Notify::Notify::instance().send_full(x,y,z) //x=headline, y= message , z = GdkPixbuf*


/* Sets the icon for the next and ONLY the next notification.
 * 'x' must be a char* to one of the stock-icon names
 * you can find on 'http://standards.freedesktop.org/icon-naming-spec/icon-naming-spec-latest.html'
 *  DO NOT FORGET TO ACTUALLY SHOW THE NOTIFICATION!!!!!!!!!! Otherwise the next notification will have your icon if it's not re-setted.
 * Nothing serious though :)
 */
#define NOTIFY_STOCK_ICON(x) Notify::Notify::instance().set_stock_icon(x)


/* Next and ONLY NEXT notification will be seperate to all others and closes after notify-timeout set in config */
#define NOTIFY_EXTRA() Notify::Notify::instance().set_next_extra()


#endif
