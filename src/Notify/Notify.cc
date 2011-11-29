#include "Notify.hh"
#include <libnotify/notify.h>
#include "../Config/Handler.hh"
#include "../Log/Writer.hh"
namespace Notify
{
    Notify::Notify()
    {
        re_init();
        icon=NULL;
    }
    //---------------------------
    Notify::~Notify()
    {
        if(notify_is_initted())
            notify_uninit();

        clear_icon();
    }
    //---------------------------
    /* Wrapper functions ... phiu I'm cool for providing all possible combinations of char* and ustring. Right? */
    //---------------------------
    void Notify::send(Glib::ustring &msg)
    {
        _send(NULL,msg.c_str(),NULL);
    }
    //---------------------------
    void Notify::send_big(Glib::ustring &hl, Glib::ustring &msg)
    {
        _send(hl.c_str(),msg.c_str(),NULL);
    }
    //---------------------------
    void Notify::send_pic(Glib::ustring &msg, GdkPixbuf * pixbuf)
    {
        _send(NULL,msg.c_str(),pixbuf);
    }
    //---------------------------
    void Notify::send_full(Glib::ustring &hl, Glib::ustring &msg, GdkPixbuf * pixbuf )
    {
        _send(hl.c_str(),msg.c_str(),pixbuf);
    }
    //---------------------------
    //---------------------------
    void Notify::send(const char *msg)
    {
        _send(NULL,msg,NULL);
    }
    //---------------------------
    void Notify::send_big(const char *hl, const char *msg)
    {
        _send(hl,msg,NULL);
    }
    //---------------------------
    void Notify::send_big(Glib::ustring &hl, const char *msg)
    {
        _send(hl.c_str(),msg,NULL);
    }
    //---------------------------
    void Notify::send_big(const char *hl, Glib::ustring &msg)
    {
        _send(hl,msg.c_str(),NULL);
    }
    //---------------------------
    void Notify::send_pic(const char *msg, GdkPixbuf * pixbuf)
    {
        _send(NULL,msg,pixbuf);
    }
    //---------------------------
    void Notify::send_full(const char *hl, const char *msg, GdkPixbuf * pixbuf )
    {
        _send(hl,msg,pixbuf);
    }
    //---------------------------
    void Notify::send_full(Glib::ustring &hl, const char *msg, GdkPixbuf * pixbuf )
    {
        _send(hl.c_str(),msg,pixbuf);
    }
    //---------------------------
    void Notify::send_full(const char *hl, Glib::ustring &msg, GdkPixbuf * pixbuf )
    {
        _send(hl,msg.c_str(),pixbuf);
    }
    //---------------------------
    /**/
    //---------------------------
    void Notify::_send(const char * hl, const char  * msg, GdkPixbuf * pixbuf )
    {

        if(use_notify && notify_is_initted())
        {

            NotifyNotification *notification=notify_notification_new(
            hl!=NULL?hl:NULL,
            msg!=NULL?msg:NULL,
            icon!=NULL?icon->c_str():NULL
            );

            if(pixbuf!=NULL)
            {
                notify_notification_set_image_from_pixbuf(notification,pixbuf);
            }

            notify_notification_set_timeout(notification,timeout);

            /* relevant only for notification daemon */
//            notify_notification_set_category(notification,"Freya");

            /* not used now
            notify_notification_set_urgency (notification,NOTIFY_URGENCY_NORMAL);
            */


            GError *er=NULL;

            /* shows the notification */
            notify_notification_show(notification,&er);

            if(er != NULL)
                Error("An Error occured showing the Notification");

            clear_icon();

        }

    }
    //------------------------
    void Notify::re_init(void)
    {


        if(notify_is_initted())
            notify_uninit();

        this->timeout = CONFIG_GET_AS_INT("settings.libnotify.timeout");
        this->use_notify = CONFIG_GET_AS_INT("settings.libnotify.signal");

        clear_icon();

        if(use_notify)
        {

            if(!notify_init("Freya"))
            {
                Error("Libnotify reports it's not working.");
            }

        }
    }

    //------------------------

    void Notify::set_stock_icon(const char* name)
    {
        clear_icon();
        icon = new Glib::ustring(name);
    }

    void Notify::clear_icon(void)
    {
        if(icon !=NULL)
        {
            delete icon;
            icon=NULL;
        }
    }
}
