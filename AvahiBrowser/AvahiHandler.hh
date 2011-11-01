#ifndef FREYA_AVAHI_HANDLER_HH 
#define FREYA_AVAHI_HANDLER_HH 

#include "AvahiView.hh"

#include <avahi-client/client.h>
#include <avahi-client/lookup.h>
#include <avahi-common/error.h>
#include <avahi-glib/glib-watch.h>
#include <avahi-glib/glib-malloc.h>

class FreyaAvahiHandler
{
    public:

    FreyaAvahiHandler();
    ~FreyaAvahiHandler();
    FreyaAvahiView& get_window(void);

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

        /* vars */
        AvahiClient * client;
        AvahiGLibPoll * glib_poll;
        FreyaAvahiView window;
};

#endif // FREYA_AVAHI_HANDLER_HH 
