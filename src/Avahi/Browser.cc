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
#include "Browser.hh"
#include "../Log/Writer.hh"

/* For: g_sprintf */
#include <glib.h>
#include <glib/gprintf.h>

/* What type of services to browse */
#define MPD_AVAHI_SERVICE_TYPE "_mpd._tcp"

/*
 * Please beware dear reader:
 * Avahi is forcing me to do those long and unfunny looking callbacks.
 * Sadly they don't offer a nice C++ API..
 */

namespace Avahi
{
    void Browser::check_client_error(const gchar * prefix_message)
    {
        /* Print just a message for now */
        if(avahi_client_errno(client) != AVAHI_OK)
        {
            const gchar * error_message = avahi_strerror(avahi_client_errno(client));
            window->set_status(error_message);
            Warning("%s: %s",prefix_message,error_message);
        }
    }

    /* --------------------------------------- */

    /* STATUS CALLBACK */

    /* Callback for state changes on the Client */
    void Browser::client_callback (AVAHI_GCC_UNUSED AvahiClient *client, AvahiClientState state)
    {
        Info("Avahi Client State Change: %d", state);
        if (state == AVAHI_CLIENT_FAILURE)
        {
            /* We we're disconnected from the Daemon */
            check_client_error("Disconnected from the Avahi Daemon");
        }
    }

    /* --------------------------------------- */

    /* static wrapper for the callback */
    void Browser::wrap_client_callback(AVAHI_GCC_UNUSED AvahiClient *client,
            AvahiClientState state,
            void * self)
    {
        Browser * myself = (Browser*)self;
        myself->client_callback(client,state);
    }

    /* --------------------------------------- */

    /* RESOLVER CALLBACK */

    /* Called whenever a service has been resolved successfully or timed out */
    void Browser::resolve_callback(
            AvahiServiceResolver * resolver,
            AVAHI_GCC_UNUSED AvahiIfIndex interface,
            AVAHI_GCC_UNUSED AvahiProtocol protocol,
            AvahiResolverEvent event,
            const char *name,
            const char *type,
            const char *domain,
            const char *host_name,
            const AvahiAddress *address,
            uint16_t port,
            AVAHI_GCC_UNUSED AvahiStringList *txt,
            AVAHI_GCC_UNUSED AvahiLookupResultFlags flags) 
    {

        if(resolver == NULL)
        {
            return;
        }

        /* Check if we had been successful */
        switch(event) 
        {
            case AVAHI_RESOLVER_FAILURE:
                {
                    gchar * format = g_strdup_printf("Failed to resolve service '%s' of type '%s' in domain '%s'", name, type, domain);
                    check_client_error("Failed to resolve service ");
                    g_free(format);
                    break;
                }
            case AVAHI_RESOLVER_FOUND: 
                {
                    /* Get the IP */
                    char addr[AVAHI_ADDRESS_STR_MAX];
                    avahi_address_snprint(addr, sizeof(addr), address);

                    Info("=> '%s' of type '%s' in domain '%s':", name, type, domain);
                    Info("=> %s:%u (%s)",host_name, port, addr);

                    /* Add in View */
                    window->server_append(addr,host_name, name, port);
                }
        }

        avahi_service_resolver_free(resolver);
    }

    /* --------------------------------------- */

    /* static wrapper for the resolver callback */
    void Browser::wrap_resolve_callback(AvahiServiceResolver * r,
            AvahiIfIndex interface,
            AvahiProtocol protocol,
            AvahiResolverEvent event,
            const char *name,
            const char *type,
            const char *domain,
            const char *host_name,
            const AvahiAddress *address,
            uint16_t port,
            AvahiStringList *txt,
            AvahiLookupResultFlags flags,
            void * self)
    {
        Browser * myself = (Browser*)self;
        myself->resolve_callback(r,interface,protocol,event,name,type,domain,host_name,address,port,txt,flags);
    }

    /* --------------------------------------- */

    /* SERVICE BROWSER CALLBACK */
    void Browser::service_browser_callback(AvahiServiceBrowser *b,
            AvahiIfIndex interface,
            AvahiProtocol protocol,
            AvahiBrowserEvent event, 
            const char *name,
            const char *type,
            const char *domain, 
            AVAHI_GCC_UNUSED AvahiLookupResultFlags flags) 
    {
        /* Necessary since this may block till client is fully connected */
        AvahiClient * full_client = avahi_service_browser_get_client(b);

        /* Check event, comments from the avahi documentation. */
        switch(event)
        {
            /* The object is new on the network.*/
            case AVAHI_BROWSER_NEW:
                {
                    Info("-- NEW: %s %s %s",name,type,domain);
                    if(avahi_service_resolver_new(full_client, interface, protocol, name, type, domain,
                                (AvahiLookupFlags)AVAHI_PROTO_INET, (AvahiLookupFlags)0, 
                                Browser::wrap_resolve_callback, this) == NULL)
                    {
                        gchar * format = g_strdup_printf("Failed to resolve service '%s'",name);
                        check_client_error(format);
                        g_free(format);
                    }
                    server_counter++;
                    update_status_label(); 
                    break;
                }
                /* The object has been removed from the network.*/
            case AVAHI_BROWSER_REMOVE:
                {
                    Info("-- DEL: %s %s %s",name,type,domain);
                    window->server_delete(name);
                    server_counter--;
                    update_status_label(); 
                    break;
                }
                /* One-time event, to notify the user that all entries from the caches have been sent. */
            case AVAHI_BROWSER_CACHE_EXHAUSTED:
                {
                    break;
                }
                /* One-time event, to notify the user that more records will probably not show up in the near future, i.e.
                 * all cache entries have been read and all static servers been queried */
            case AVAHI_BROWSER_ALL_FOR_NOW:
                {
                    Info("-- Got all domains for now...");
                    update_status_label(); 
                    break;
                }
                /* Browsing failed due to some reason which can be retrieved using avahi_server_errno()/avahi_client_errno() */
            case AVAHI_BROWSER_FAILURE:
                {
                    check_client_error("Error while browsing");
                    break;
                }
            default: 
                break;
        }
    }

    /* --------------------------------------- */

    /* static wrapper for service callbacks */
    void Browser::wrap_service_browser_callback(AvahiServiceBrowser *b,
            AvahiIfIndex interface,
            AvahiProtocol protocol,
            AvahiBrowserEvent event, 
            const char *name,
            const char *type,
            const char *domain, 
            AvahiLookupResultFlags flags,
            void * userdata)
    {
        Browser * myself = (Browser*)userdata;
        myself->service_browser_callback(b,interface,protocol,event,name,type,domain,flags);
    }

    /* --------------------------------------- */

    /* CTor */
    Browser::Browser(void) 
    {
        const AvahiPoll *poll_api;
        int error = 0;

        server_counter = 0;

        /* Build View */
        window = new View();

        /* Optional: Tell avahi to use g_malloc and g_free */
        avahi_set_allocator (avahi_glib_allocator());

        /* Create the GLIB Adaptor */
        glib_poll = avahi_glib_poll_new (NULL, Glib::PRIORITY_HIGH);
        poll_api = avahi_glib_poll_get (glib_poll);

        /* Create a new AvahiClient instance */
        client = avahi_client_new(poll_api,(AvahiClientFlags)AVAHI_CLIENT_NO_FAIL,
                Browser::wrap_client_callback,this,&error);

        /* Check the error return code */
        if(client != NULL && avahi_client_get_state(client) != AVAHI_CLIENT_CONNECTING)
        {
            avahi_service_browser_new(client,
                    AVAHI_IF_UNSPEC,
                    AVAHI_PROTO_UNSPEC,
                    MPD_AVAHI_SERVICE_TYPE,
                    avahi_client_get_domain_name(client),
                    (AvahiLookupFlags)0,
                    Browser::wrap_service_browser_callback, this);
        }
        else
        {
            if(client != NULL)
            {
                check_client_error("Initializing Avahi");
            }

            delete window;
            window = NULL;
        }
    }

    /* --------------------------------------- */

    /* DTor */
    Browser::~Browser(void)
    {
        delete window;
        if(client != NULL)
            avahi_client_free(client);

        if(glib_poll != NULL)
            avahi_glib_poll_free(glib_poll);
    }

    /* --------------------------------------- */

    View& Browser::get_window(void)
    {
        return *(window);
    }

    /* --------------------------------------- */

    /* Check if this browser has a working connection */
    bool Browser::is_connected(void)
    {
        return !(window == NULL);
    }

    /* --------------------------------------- */

    SelectNotify& Browser::signal_selection_done(void)
    {
        return window->signal_select;
    }

    /* --------------------------------------- */

    void Browser::update_status_label(void)
    {
        char msg_buf[128] = {0};
        g_sprintf(msg_buf,"Found %d server%s",server_counter,(server_counter == 1) ? "" : "s");
        window->set_status(msg_buf);
    }

    /* --------------------------------------- */
}
