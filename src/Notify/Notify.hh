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
        friend class NotifyTestSuite;

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
