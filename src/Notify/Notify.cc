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

        if(notification!=NULL)
            g_object_unref(G_OBJECT(notification));
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
            NotifyNotification *notification_ptr;
            if(extra)
            {
                notification_ptr=notify_notification_new(
                    hl!=NULL?hl:"",
                    msg!=NULL?msg:"",
                    icon!=NULL?icon->c_str():NULL
                );

            }
            else
            {
                notify_notification_update(
                    notification,
                    hl!=NULL?hl:"",
                    msg!=NULL?msg:"",
                    icon!=NULL?icon->c_str():NULL
                );
                notification_ptr = notification;
            }

            if(pixbuf!=NULL)
            {
                notify_notification_set_image_from_pixbuf(notification_ptr,pixbuf);
            }
            notify_notification_set_timeout(notification_ptr,timeout);

            GError *er=NULL;

            /* shows the notification */
            notify_notification_show(notification_ptr,&er);
            if(er!=NULL)
                Warning("There hase been a problem while trying to display the notification!");
            if(extra)
            {
                extra=false;
                g_object_unref(G_OBJECT(notification_ptr));
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
                    Warning("Libnotify reports it's not working.");
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
