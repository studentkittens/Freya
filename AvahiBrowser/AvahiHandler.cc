#include "AvahiHandler.hh"

/* What type of services to browse */
#define MPD_AVAHI_SERVICE_TYPE "_mpd._tcp"

/// STATUS CALLBACK ///

/* Callback for state changes on the Client */
void FreyaAvahiHandler::client_callback (AVAHI_GCC_UNUSED AvahiClient *client, AvahiClientState state)
{
    g_message("Avahi Client State Change: %d", state);
    if (state == AVAHI_CLIENT_FAILURE)
    {
        /* We we're disconnected from the Daemon */
        g_message("Disconnected from the Avahi Daemon: %s", avahi_strerror(avahi_client_errno(client)));
    }
}

/* static wrapper for the callback */

void FreyaAvahiHandler::wrap_client_callback(AVAHI_GCC_UNUSED AvahiClient *client, AvahiClientState state, AVAHI_GCC_UNUSED void * self)
{
    FreyaAvahiHandler * myself = (FreyaAvahiHandler*)self;
    myself->client_callback(client,state);
}


/// RESOLVER CALLBACK ///

/* Called whenever a service has been resolved successfully or timed out */
void FreyaAvahiHandler::resolve_callback(
        AvahiServiceResolver * r,
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

    assert(r);


    switch(event) 
    {
        case AVAHI_RESOLVER_FAILURE:
            {
                g_message("(Resolver) Failed to resolve service '%s' of type '%s' in domain '%s': %s\n", name, type, domain, avahi_strerror(avahi_client_errno(avahi_service_resolver_get_client(r))));
                break;
            }
        case AVAHI_RESOLVER_FOUND: 
            {
                char addr[AVAHI_ADDRESS_STR_MAX];
                avahi_address_snprint(addr, sizeof(addr), address);

                g_message("=> '%s' of type '%s' in domain '%s':", name, type, domain);
                g_message("=> %s:%u (%s)",host_name, port, addr);

                this->window.server_append(addr,host_name, name, port);
            }
    }

    avahi_service_resolver_free(r);
}

/* static wrapper for the resolver callback */

void FreyaAvahiHandler::wrap_resolve_callback(AvahiServiceResolver * r,AvahiIfIndex interface, AvahiProtocol protocol,AvahiResolverEvent event,
        const char *name, const char *type, const char *domain, const char *host_name, const AvahiAddress *address,
        uint16_t port, AvahiStringList *txt, AvahiLookupResultFlags flags, void* self)
{
    FreyaAvahiHandler * myself = (FreyaAvahiHandler*)self;
    myself->resolve_callback(r,interface,protocol,event,name,type,domain,host_name,address,port,txt,flags);
}


/// SERVICE BROWSER CALLBACK ///

void FreyaAvahiHandler::service_browser_callback(AvahiServiceBrowser *b, AvahiIfIndex interface, AvahiProtocol protocol, AvahiBrowserEvent event, 
        const char *name, const char *type, const char *domain, 
        AVAHI_GCC_UNUSED AvahiLookupResultFlags flags) 
{
    AvahiClient * client = avahi_service_browser_get_client(b);

    switch(event)
    {
        case AVAHI_BROWSER_NEW:
            /* The object is new on the network.*/
            g_message("-- NEW: %s %s %s",name,type,domain);
            if(avahi_service_resolver_new(client, interface, protocol, name, type, domain, (AvahiLookupFlags)AVAHI_PROTO_UNSPEC, (AvahiLookupFlags)0, FreyaAvahiHandler::wrap_resolve_callback, this)  ==  NULL)
            {
                g_message("Failed to resolve service '%s': %s\n", name, avahi_strerror(avahi_client_errno(client)));
            }
            break;
        case AVAHI_BROWSER_REMOVE:
            /* The object has been removed from the network.*/
            g_message("-- DEL: %s %s %s",name,type,domain);
            window.server_delete(name);
            break;
        case AVAHI_BROWSER_CACHE_EXHAUSTED:
            /* One-time event, to notify the user that all entries from the caches have been sent. */
            g_message("-- Cache is exhausted. Whatever that means.");
            break;
        case AVAHI_BROWSER_ALL_FOR_NOW:
            /* One-time event, to notify the user that more records will probably not show up in the near future, i.e.
             * all cache entries have been read and all static servers been queried */
            g_message("-- Got all domains for now...");
            window.set_status("Done with searching for now.   ");
            break;
        case AVAHI_BROWSER_FAILURE:
            /* Browsing failed due to some reason which can be retrieved using avahi_server_errno()/avahi_client_errno() */
            g_message("An error during browsing avahi services:");
            g_message("-- Clientmessage: %s",avahi_strerror(avahi_client_errno(client)));
            window.set_status(avahi_strerror(avahi_client_errno(client)));
            break;
        default: 
            /* empty */
            break;
    }
}
void FreyaAvahiHandler::wrap_service_browser_callback(AvahiServiceBrowser *b, AvahiIfIndex interface, AvahiProtocol protocol, AvahiBrowserEvent event, 
        const char *name, const char *type, const char *domain, 
        AVAHI_GCC_UNUSED AvahiLookupResultFlags flags, void * userdata)
{
    FreyaAvahiHandler * myself = (FreyaAvahiHandler*)userdata;
    myself->service_browser_callback(b,interface,protocol,event,name,type,domain,flags);
}


/// CTor ///

FreyaAvahiHandler::FreyaAvahiHandler(void) : window()
{
    const AvahiPoll *poll_api;
    int error = 0;

    /* Optional: Tell avahi to use g_malloc and g_free */
    avahi_set_allocator (avahi_glib_allocator());

    /* Create the GLIB Adaptor */
    this->glib_poll = avahi_glib_poll_new (NULL, G_PRIORITY_DEFAULT);
    poll_api = avahi_glib_poll_get (this->glib_poll);

    /* Create a new AvahiClient instance */
    this->client = avahi_client_new (poll_api,(AvahiClientFlags)0,FreyaAvahiHandler::wrap_client_callback,this,&error);

    /* Check the error return code */
    if(this->client != NULL)
    {
        avahi_service_browser_new(this->client,
                AVAHI_IF_UNSPEC,
                AVAHI_PROTO_UNSPEC,
                MPD_AVAHI_SERVICE_TYPE,
                avahi_client_get_domain_name(this->client),
                (AvahiLookupFlags)0,
                FreyaAvahiHandler::wrap_service_browser_callback, this);
    }
    else
    {
        /* Print out the error string */
        g_warning ("Error initializing Avahi: %s", avahi_strerror (error));
    }
}

/// DTor ///

FreyaAvahiHandler::~FreyaAvahiHandler(void)
{
    if(this->client != NULL)
        avahi_client_free(this->client);

    if(this->glib_poll != NULL)
        avahi_glib_poll_free(this->glib_poll);
}

/// For testing purpose.. ///

FreyaAvahiView& FreyaAvahiHandler::get_window(void)
{
    return this->window;
}
