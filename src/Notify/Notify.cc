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
//---------------------------
    /**/
//---------------------------
    void Notify::_send(const char * hl, const char  * msg, GdkPixbuf * pixbuf )
    {

        while(working);

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
        while(working);

        {
            working=true;


            if(notify_is_initted())
                notify_uninit();

            this->timeout = CONFIG_GET_AS_INT("settings.libnotify.timeout");
            this->use_notify = CONFIG_GET_AS_INT("settings.libnotify.signal");

            clear_icon();
            extra=false;

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
