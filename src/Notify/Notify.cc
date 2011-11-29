#include "Notify.hh"
#include "../Config/Handler.hh"
#include "../Log/Writer.hh"
#include <libnotify/notify.h>

namespace Notify
{
    Notify::Notify()
    {
        re_init();
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
    //---------------------------
    void Notify::send_big(Glib::ustring hl, Glib::ustring msg)
    {
        _send(hl.c_str(),msg.c_str(),NULL);
    }
    //---------------------------
    void Notify::send_full(Glib::ustring hl, Glib::ustring msg, GdkPixbuf * pixbuf )
    {
        _send(hl.c_str(),msg.c_str(),pixbuf);
    }
    //---------------------------
    void Notify::send_big(const char *hl, const char *msg)
    {
        _send(hl,msg,NULL);
    }
    //---------------------------
    void Notify::send_big(Glib::ustring hl, const char *msg)
    {
        _send(hl.c_str(),msg,NULL);
    }
    //---------------------------
    void Notify::send_big(const char *hl, Glib::ustring msg)
    {
        _send(hl,msg.c_str(),NULL);
    }
    //---------------------------
    void Notify::send_full(const char *hl, const char *msg, GdkPixbuf * pixbuf )
    {
        _send(hl,msg,pixbuf);
    }
    //---------------------------
    void Notify::send_full(Glib::ustring hl, const char *msg, GdkPixbuf * pixbuf )
    {
        _send(hl.c_str(),msg,pixbuf);
    }
    //---------------------------
    void Notify::send_full(const char *hl, Glib::ustring msg, GdkPixbuf * pixbuf )
    {
        _send(hl,msg.c_str(),pixbuf);
    }
    //---------------------------
    /**/
    //---------------------------
    void Notify::_send(const char * hl, const char  * msg, GdkPixbuf * pixbuf )
    {

        if(use_notify && !working && notify_is_initted())
        {
            working=true;

            if(extra)
            {
                NotifyNotification *notification2=notify_notification_new(
                    hl!=NULL?hl:NULL,
                    msg!=NULL?msg:NULL,
                    icon!=NULL?icon->c_str():NULL
                );

                if(pixbuf!=NULL)
                {
                    notify_notification_set_image_from_pixbuf(notification2,pixbuf);
                }

                notify_notification_set_timeout(notification2,timeout);

                GError *er=NULL;

                /* shows the notification */
                notify_notification_show(notification2,&er);

                if(er != NULL)
                    Error("An Error occured showing the Notification");
                extra=false;
            }
            else
            {
                notify_notification_update(
                    notification,
                    hl!=NULL?hl:NULL,
                    msg!=NULL?msg:NULL,
                    icon!=NULL?icon->c_str():NULL
                );

                if(pixbuf!=NULL)
                {
                    notify_notification_set_image_from_pixbuf(notification,pixbuf);
                }

                notify_notification_set_timeout(notification,timeout);

                GError *er=NULL;

                /* shows the notification */
                notify_notification_show(notification,&er);

            }

            clear_icon();
            working=false;
        }
    }
    //------------------------
    void Notify::re_init(void)
    {
        if(!working)
        {
            working=true;


            if(notify_is_initted())
                notify_uninit();

            this->timeout = CONFIG_GET_AS_INT("settings.libnotify.timeout");
            this->use_notify = CONFIG_GET_AS_INT("settings.libnotify.signal");

            clear_icon();
            extra=false;
            icon=NULL;
            notification = notify_notification_new("Freya",NULL,NULL);

            if(use_notify)
            {
                if(!notify_init("Freya"))
                {
                    Error("Libnotify reports it's not working.");
                }
            }

            working=false;
        }
    }

    //------------------------

    void Notify::set_stock_icon(const char* name)
    {
        clear_icon();
        icon = new Glib::ustring(name);
    }
    //------------------------

    void Notify::clear_icon(void)
    {
        if(icon !=NULL)
        {
            delete icon;
            icon=NULL;
        }
    }
    //------------------------

    void Notify::set_next_extra(void)
    {
        extra=true;
    }
    //------------------------
}
