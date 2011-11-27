#ifndef FREYA_NOTIFY_GUARD
#define FREYA_NOTIFY_GUARD

#include "../Singleton.hh"
#include <gtkmm.h>

/*----> THIS IS JUST A TEST. THIS IS NOT MEANT TO BE A REAL NOTIFICATIONSYSTEM. <----*/
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
        private:
            void re_init(void);
            int timeout,use_notify;
            void _send(Glib::ustring *hl, Glib::ustring *msg, GdkPixbuf * pixbuf);
    };
}

#define NOTIFY_SEND(x) Notify::Notify::instance().send(x)   //x=message
#define NOTIFY_SEND_W_HEADLINE(x,y) Notify::Notify::instance().send_big(x,y)    //x=headline, y=message
#define NOTIFY_SEND_W_PIC(x,y) Notify::Notify::instance().send_pic(x,y)     //x=message, y= GdkPixbuf*
#define NOTIFY_SEND_FULL(x,y,z) Notify::Notify::instance().send_full(x,y,z) //x=headline, y= message , z = GdkPixbuf*

#endif
