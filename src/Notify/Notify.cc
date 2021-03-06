/***********************************************************
 * This file is part of Freya
 * - A free MPD Gtk3 MPD Client -
 *
 * Authors: Christopher Pahl, Christoph Piechula,
 *          Eduard Schneider
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

#define THREAD_TERMINATOR ((gpointer)0x1)

namespace Notify
{
/*
 * Worker Thread,
 * waits for notifications to show
 */
gpointer send_notify_signal(gpointer v_async_queue)
{
    GAsyncQueue * async_queue = (GAsyncQueue*)v_async_queue;
    while(true)
    {
        gpointer job = g_async_queue_pop(async_queue);
        if(job == THREAD_TERMINATOR)
        {
            g_async_queue_unref(async_queue);
            return NULL;
        }
        else
        {
            GError * err = NULL;
            NotifyNotification * noti_obj = (NotifyNotification*)job;
            notify_notification_show(noti_obj,&err);
            if(err != NULL)
            {
                Warning("Unable to show notification: %s",err->message);
                g_error_free(err);
            }
            else
            {
                g_object_unref(G_OBJECT(noti_obj));
            }
        }
    }
    return NULL;
}

//////////////////

Notify::Notify() :
    timeout(0),
    use_notify(false),
    extra(false),
    async_queue(g_async_queue_new())
{
    GError * err = NULL;
    g_thread_create(send_notify_signal,async_queue,false,&err);
    if(err != NULL)
    {
        Warning("Cannot create Notify Thread: %s",err->message);
        g_error_free(err);
    }
}

//////////////////

Notify::~Notify()
{
    g_async_queue_push(async_queue,THREAD_TERMINATOR);
}

//////////////////

void Notify::do_init()
{
    timeout = CONFIG_GET_AS_INT("settings.libnotify.timeout");
    use_notify = CONFIG_GET_AS_INT("settings.libnotify.signal");
    if(use_notify && notify_is_initted() == false)
    {
        notify_init("Freya");
        atexit(notify_uninit);
    }
}


//////////////////

void Notify::_send(const char * summary, const char  * msg, const char * icon_name)
{
    if(summary == NULL)
    {
        Warning("Notify::_send() requires at least a summary.");
        return;
    }
    do_init();
    if(use_notify == false)
        return;
    NotifyNotification * noti_obj = notify_notification_new(summary,msg,icon_name);
    if(noti_obj != NULL)
    {
        /*
         * For some reason showing the notification
         * is rather expensive, we do it in a separate thread
         * therefore.
         */
        g_async_queue_push(async_queue,noti_obj);
    }
}

//////////////////

void Notify::send_big(Glib::ustring hl, Glib::ustring msg)
{
    _send(hl.c_str(),msg.c_str(),NULL);
}

//////////////////

void Notify::send_full(Glib::ustring hl, Glib::ustring msg, GdkPixbuf * pixbuf)
{
    _send(hl.c_str(),msg.c_str(),NULL);
}

//////////////////

void Notify::set_next_extra()
{
    extra = true;
}

//////////////////

void Notify::set_stock_icon(const char* name)
{
    icon_name = Glib::ustring(name);
}

//////////////////
}
