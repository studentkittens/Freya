#include "Notify.hh"
#include "../Log/Writer.hh"
#include <glib.h>
#include <libnotify/notify.h>
#include "../Config/Handler.hh"
//#include <gdk-pixbuf/gdk-pixbuf.h>

namespace Notify
{
    Notify::Notify()
    {
        re_init();
    }
    //---------------------------
    Notify::~Notify()
    {
        notify_uninit();
    }
    //---------------------------
    /* Wrapper functions */
    //---------------------------
    void Notify::send(Glib::ustring &msg)
    {
        _send(NULL,&msg,NULL);
    }
    //---------------------------
    void Notify::send_big(Glib::ustring &hl, Glib::ustring &msg)
    {
        _send(&hl,&msg,NULL);
    }
    //---------------------------
    void Notify::send_pic(Glib::ustring &msg, GdkPixbuf * pixbuf)
    {
        _send(NULL,&msg,pixbuf);
    }
    //---------------------------
    void Notify::send_full(Glib::ustring &hl, Glib::ustring &msg, GdkPixbuf * pixbuf )
    {
        _send(&hl,&msg,pixbuf);
    }
    //---------------------------
    /**/
    //---------------------------
    void Notify::_send(Glib::ustring * hl, Glib::ustring  * msg, GdkPixbuf * pixbuf )
    {
        if(use_notify && notify_is_initted())
        {
            NotifyNotification *notification=notify_notification_new(
            hl!=NULL?hl->c_str():NULL,
            msg!=NULL?msg->c_str():NULL,
            NULL
            );

            if(pixbuf!=NULL)
            {
                notify_notification_set_image_from_pixbuf(notification,pixbuf);
            }

            notify_notification_set_timeout(notification,timeout);

            /* relevant only for notification daemon */
            notify_notification_set_category(notification,"Freya");

            /* not used now
            notify_notification_set_urgency (notification,NOTIFY_URGENCY_NORMAL);
            */


            GError *er=NULL;

            /* shows the notification */
            notify_notification_show(notification,&er);

            if(er != NULL)
                Error("An Error occured showing the Notification");
        }

    }
    //------------------------
    void Notify::re_init(void)
    {

        if(notify_is_initted())
            notify_uninit();

        this->timeout = CONFIG_GET_AS_INT("settings.libnotify.timeout");
        this->use_notify = CONFIG_GET_AS_INT("settings.libnotify.signal");

        if(use_notify)
        {
            if(!notify_init("Freya"))
            {
                Error("Libnotify reports it's not working.");
            }
        }
    }

    //------------------------
}
