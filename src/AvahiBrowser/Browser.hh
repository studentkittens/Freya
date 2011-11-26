#ifndef FREYA_AVAHI_BROWSER_HH
#define FREYA_AVAHI_BROWSER_HH

#include "View.hh"

/* Avahi stuff */
#include <avahi-client/client.h>
#include <avahi-client/lookup.h>
#include <avahi-common/error.h>
#include <avahi-glib/glib-watch.h>
#include <avahi-glib/glib-malloc.h>

namespace Avahi
{
    class Browser
    {
        public:

            Browser();
            ~Browser();
            View& get_window(void);
            bool is_connected(void);

            sigc::signal<void,Glib::ustring,Glib::ustring,Glib::ustring, unsigned int>& get_signal(void);

        private:
            /* methods */
            void client_callback(AVAHI_GCC_UNUSED AvahiClient *client, AvahiClientState state);
            static void wrap_client_callback(AVAHI_GCC_UNUSED AvahiClient *client, AvahiClientState state, AVAHI_GCC_UNUSED void * self);

            /* Argh... Avahi loves huge functions */
            void resolve_callback(AvahiServiceResolver * r,AvahiIfIndex interface, AvahiProtocol protocol,AvahiResolverEvent event,
                    const char *name, const char *type, const char *domain, const char *host_name, const AvahiAddress *address,
                    uint16_t port, AvahiStringList *txt, AvahiLookupResultFlags flags);

            static void wrap_resolve_callback(AvahiServiceResolver * r,AvahiIfIndex interface, AvahiProtocol protocol,AvahiResolverEvent event,
                    const char *name, const char *type, const char *domain, const char *host_name, const AvahiAddress *address,
                    uint16_t port, AvahiStringList *txt, AvahiLookupResultFlags flags, void* userdata);

            /* Servicebrowser callback.. *sigh* Why am I writing this ton of params */
            void service_browser_callback(AvahiServiceBrowser *b, AvahiIfIndex interface, AvahiProtocol protocol, AvahiBrowserEvent event, 
                    const char *name, const char *type, const char *domain, 
                    AVAHI_GCC_UNUSED AvahiLookupResultFlags flags); 

            static void wrap_service_browser_callback(AvahiServiceBrowser *b, AvahiIfIndex interface, AvahiProtocol protocol, AvahiBrowserEvent event, 
                    const char *name, const char *type, const char *domain, 
                    AVAHI_GCC_UNUSED AvahiLookupResultFlags flags, void * userdata); 

            void check_client_error(const gchar * prefix_message);

            void update_status_label(void);

            /* vars */
            AvahiClient * client;
            AvahiGLibPoll * glib_poll;
            View * window;

            unsigned server_counter;
    };
}

#endif // FREYA_AVAHI_BROWSER_HH 
