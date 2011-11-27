#include "Notify.hh"
#include "../Log/Writer.hh"
#include <glib.h>
#include <libnotify/notify.h>
#include "../Config/Handler.hh"


namespace Notify
{
    Notify::Notify()
    {
        if(!notify_init("Freya"))
            Error("Libnotify reports it's not working.");
    }
    //---------------------------
    Notify::~Notify()
    {
        notify_uninit();
    }
    //---------------------------
    void Notify::send(Glib::ustring msg)
    {
        if(notify_is_initted())
        {
            NotifyNotification *notification=notify_notification_new(msg.c_str(),NULL,NULL);
            notify_notification_set_timeout(notification,1);
            notify_notification_set_category(notification,"Freya");
            notify_notification_set_urgency (notification,NOTIFY_URGENCY_NORMAL);
            GError *er=NULL;
            notify_notification_show(notification,&er);
            if(er != NULL)
                Error("An Error occured showing the Notification");
        }
    }
}
