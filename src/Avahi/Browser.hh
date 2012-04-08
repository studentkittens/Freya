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
#ifndef FREYA_AVAHI_BROWSER_HH
#define FREYA_AVAHI_BROWSER_HH

#include "../../config.h"

#if USE_AVAHI

/* Avahi stuff */
#include <avahi-client/client.h>
#include <avahi-client/lookup.h>
#include <avahi-common/error.h>
#include <avahi-glib/glib-watch.h>
#include <avahi-glib/glib-malloc.h>

#include <glibmm.h>


namespace Avahi
{
/**
 * @brief Called when the user selectes a server from the list
 */
typedef sigc::signal<void,Glib::ustring,Glib::ustring,Glib::ustring,unsigned> GotServerNotify;
typedef sigc::signal<void,Glib::ustring> DeleteServerNotify;
typedef sigc::signal<void,Glib::ustring> ErroMessageNotify;

/**
 * @brief This class offers a simple Zeroconf Serverbrowser
 */
class Browser
{
public:

    /**
     * @brief Instance the underlying browser and already start querying
     */
    Browser();

    /**
     * @brief Clean up before you can instance another one
     */
    ~Browser();

    /**
     * @brief Check if Browser is ready for use
     *
     * @return obvious.
     */
    bool is_connected();

    int get_server_count();

    GotServerNotify& signal_got_server();
    ErroMessageNotify& signal_error_message();
    DeleteServerNotify& signal_deleted_server();

private:

    void client_callback(AVAHI_GCC_UNUSED AvahiClient *client,
                         AvahiClientState state);

    static void wrap_client_callback(AVAHI_GCC_UNUSED AvahiClient *client,
                                     AvahiClientState state,
                                     void * self);

    /* Argh... Avahi loves huge functions */
    void resolve_callback(
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
        AVAHI_GCC_UNUSED AvahiLookupResultFlags flags);

    static void wrap_resolve_callback(AvahiServiceResolver * r,
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
                                      void * self);

    /* Servicebrowser callback.. *sigh* Why am I writing this ton of params..? */
    void service_browser_callback(AvahiServiceBrowser *b,
                                  AvahiIfIndex interface,
                                  AvahiProtocol protocol,
                                  AvahiBrowserEvent event,
                                  const char *name,
                                  const char *type,
                                  const char *domain,
                                  AVAHI_GCC_UNUSED AvahiLookupResultFlags flags);

    static void wrap_service_browser_callback(AvahiServiceBrowser *b,
            AvahiIfIndex interface,
            AvahiProtocol protocol,
            AvahiBrowserEvent event,
            const char *name,
            const char *type,
            const char *domain,
            AvahiLookupResultFlags flags,
            void * userdata);

    void check_client_error(const gchar * prefix_message);

    ////////////////////////

    AvahiClient * client;
    AvahiGLibPoll * glib_poll;

    unsigned server_counter;

    /*
     * Error messages
     */
    GotServerNotify m_signal_got_server;
    ErroMessageNotify m_signal_error_message;
    DeleteServerNotify m_signal_deleted_server;
};
}

#endif //USE_AVAHI

#endif // FREYA_AVAHI_BROWSER_HH 

