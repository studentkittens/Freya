#ifndef FREYA_NOTIFY_GUARD
#define FREYA_NOTIFY_GUARD

#include "../Singleton.hh"
#include <gtkmm.h>

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
            void send(Glib::ustring &msg);
            void send_big(Glib::ustring &hl, Glib::ustring &msg);
            void send_pic(Glib::ustring &msg, GdkPixbuf * pixbuf);
            void send_full(Glib::ustring &hl, Glib::ustring &msg, GdkPixbuf * pixbuf);
            void send(const char *msg);
            void send_big(const char *hl, const char *msg);
            void send_pic(const char *msg, GdkPixbuf * pixbuf);
            void send_full(const char *hl,const char *msg, GdkPixbuf * pixbuf);
            void set_stock_icon(const char*);
        private:
            Glib::ustring * icon;
            void re_init(void);
            void clear_icon(void);
            int timeout,use_notify;
            void _send(const char *hl, const char *msg, GdkPixbuf * pixbuf);
    };
}

#define NOTIFY_SEND(x) Notify::Notify::instance().send(x)   //x=message
#define NOTIFY_SEND_W_HEADLINE(x,y) Notify::Notify::instance().send_big(x,y)    //x=headline, y=message
#define NOTIFY_SEND_W_PIC(x,y) Notify::Notify::instance().send_pic(x,y)     //x=message, y= GdkPixbuf*
#define NOTIFY_SEND_FULL(x,y,z) Notify::Notify::instance().send_full(x,y,z) //x=headline, y= message , z = GdkPixbuf*

/* Sets the icon for the next and ONLY the next notification.
 * 'x' must be a char* to one of the stock-icon names
 * you can find on 'http://standards.freedesktop.org/icon-naming-spec/icon-naming-spec-latest.html'
 *  DO NOT FORGET TO ACTUALLY SHOW THE NOTIFICATION!!!!!!!!!! Otherwise the next notification will have your icon if it's not re-setted. 
 * Nothing serious though :)
 */
#define NOTIFY_STOCK_ICON(x) Notify::Notify::instance().set_stock_icon(x)



#endif
