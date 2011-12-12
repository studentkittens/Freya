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
#ifndef FREYA_NOTIFY_GUARD
#define FREYA_NOTIFY_GUARD

#include "../Singleton.hh"
#include <gtkmm.h>
#include <libnotify/notify.h>
namespace Browser
{
    class Settings;
}


namespace Notify
{
    class Notify
    {
        friend class Browser::Settings;

            DEF_SINGLETON( Notify )
        public:
            ~Notify();

            void send_big(Glib::ustring hl, Glib::ustring msg);
            void send_big(const char *hl, const char *msg);
            void send_big(Glib::ustring hl, const char *msg);
            void send_big(const char *hl, Glib::ustring msg);
            void send_full(Glib::ustring hl, Glib::ustring msg, GdkPixbuf * pixbuf);
            void send_full(const char *hl,const char *msg, GdkPixbuf * pixbuf);
            void send_full(Glib::ustring hl, const char *msg, GdkPixbuf * pixbuf);
            void send_full(const char *hl, Glib::ustring msg, GdkPixbuf * pixbuf);
            void set_stock_icon(const char*);

            void set_next_extra();
        private:
            Glib::ustring * icon;
            NotifyNotification *notification;
            bool extra,working;
            void re_init(void);
            void clear_icon(void);
            int timeout,use_notify;
            void _send(const char *hl, const char *msg, GdkPixbuf * pixbuf);
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


/* Next and ONLY NEXT notification will be seperate to all others and cant be closed manually */
#define NOTIFY_EXTRA() Notify::Notify::instance().set_next_extra()


#endif
