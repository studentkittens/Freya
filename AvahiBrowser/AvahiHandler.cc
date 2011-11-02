#include "AvahiHandler.hh"

/* What type of services to browse */
#define MPD_AVAHI_SERVICE_TYPE "_mpd._tcp"

void FreyaAvahiHandler::check_client_error(const gchar * prefix_message)
{
    /* Print just a message for now */
    const gchar * error_message = avahi_strerror(avahi_client_errno(this->client));
    this->window->set_status(error_message);
    g_warning("%s:%s",prefix_message,error_message);
}

/* STATUS CALLBACK */

/* Callback for state changes on the Client */
void FreyaAvahiHandler::client_callback (AVAHI_GCC_UNUSED AvahiClient *client, AvahiClientState state)
{
    g_message("Avahi Client State Change: %d", state);
    if (state == AVAHI_CLIENT_FAILURE)
    {
        /* We we're disconnected from the Daemon */
        check_client_error("Disconnected from the Avahi Daemon");
    }
}

/* static wrapper for the callback */
void FreyaAvahiHandler::wrap_client_callback(AVAHI_GCC_UNUSED AvahiClient *client, AvahiClientState state, AVAHI_GCC_UNUSED void * self)
{
    FreyaAvahiHandler * myself = (FreyaAvahiHandler*)self;
    myself->client_callback(client,state);
}


/* RESOLVER CALLBACK */

/* Called whenever a service has been resolved successfully or timed out */
void FreyaAvahiHandler::resolve_callback(
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
                this->check_client_error("Failed to resolve service ");
                g_free(format);
                break;
            }
        case AVAHI_RESOLVER_FOUND: 
            {
                /* Get the IP */
                char addr[AVAHI_ADDRESS_STR_MAX];
                avahi_address_snprint(addr, sizeof(addr), address);

                g_message("=> '%s' of type '%s' in domain '%s':", name, type, domain);
                g_message("=> %s:%u (%s)",host_name, port, addr);

                /* Add in View */
                this->window->server_append(addr,host_name, name, port);
            }
    }

    avahi_service_resolver_free(resolver);
}

/* static wrapper for the resolver callback */
void FreyaAvahiHandler::wrap_resolve_callback(AvahiServiceResolver * r,AvahiIfIndex interface, AvahiProtocol protocol,AvahiResolverEvent event,
        const char *name, const char *type, const char *domain, const char *host_name, const AvahiAddress *address,
        uint16_t port, AvahiStringList *txt, AvahiLookupResultFlags flags, void* self)
{
    FreyaAvahiHandler * myself = (FreyaAvahiHandler*)self;
    myself->resolve_callback(r,interface,protocol,event,name,type,domain,host_name,address,port,txt,flags);
}


/* SERVICE BROWSER CALLBACK */
void FreyaAvahiHandler::service_browser_callback(AvahiServiceBrowser *b, AvahiIfIndex interface, AvahiProtocol protocol, AvahiBrowserEvent event, 
        const char *name, const char *type, const char *domain, 
        AVAHI_GCC_UNUSED AvahiLookupResultFlags flags) 
{
    /* Necessary since this may block till client is fully connected */
    AvahiClient * full_client = avahi_service_browser_get_client(b);

    /* Check event, comments from the avahic documentation. */
    switch(event)
    {
        case AVAHI_BROWSER_NEW:
            /* The object is new on the network.*/
            g_message("-- NEW: %s %s %s",name,type,domain);
            if(avahi_service_resolver_new(full_client, interface, protocol, name, type, domain,
                                         (AvahiLookupFlags)AVAHI_PROTO_UNSPEC, (AvahiLookupFlags)0, 
                                         FreyaAvahiHandler::wrap_resolve_callback, this)  
                                         == NULL)
            {
                gchar * format = g_strdup_printf("Failed to resolve service '%s'",name);
                check_client_error(format);
                g_free(format);
            }
            break;
        case AVAHI_BROWSER_REMOVE:
            /* The object has been removed from the network.*/
            g_message("-- DEL: %s %s %s",name,type,domain);
            window->server_delete(name);
            break;
        case AVAHI_BROWSER_CACHE_EXHAUSTED:
            /* One-time event, to notify the user that all entries from the caches have been sent. */
            g_message("-- Cache is exhausted. Whatever that means.");
            break;
        case AVAHI_BROWSER_ALL_FOR_NOW:
            /* One-time event, to notify the user that more records will probably not show up in the near future, i.e.
             * all cache entries have been read and all static servers been queried */
            g_message("-- Got all domains for now...");
            window->set_status("Done with searching for now.   ");
            break;
        case AVAHI_BROWSER_FAILURE:
            /* Browsing failed due to some reason which can be retrieved using avahi_server_errno()/avahi_client_errno() */
            check_client_error("Error while browsing");
            break;
        default: 
            /* empty */
            break;
    }
}

/* static wrapper for service callbacks */
void FreyaAvahiHandler::wrap_service_browser_callback(AvahiServiceBrowser *b, AvahiIfIndex interface, AvahiProtocol protocol, AvahiBrowserEvent event, 
        const char *name, const char *type, const char *domain, 
        AVAHI_GCC_UNUSED AvahiLookupResultFlags flags, void * userdata)
{
    FreyaAvahiHandler * myself = (FreyaAvahiHandler*)userdata;
    myself->service_browser_callback(b,interface,protocol,event,name,type,domain,flags);
}

/* CTor */
FreyaAvahiHandler::FreyaAvahiHandler(void) 
{
    const AvahiPoll *poll_api;
    int error = 0;

    /* Build View */
    this->window = new FreyaAvahiView();

    /* Optional: Tell avahi to use g_malloc and g_free */
    avahi_set_allocator (avahi_glib_allocator());

    /* Create the GLIB Adaptor */
    this->glib_poll = avahi_glib_poll_new (NULL, G_PRIORITY_DEFAULT);
    poll_api = avahi_glib_poll_get (this->glib_poll);

    /* Create a new AvahiClient instance */
    this->client = avahi_client_new(poll_api,(AvahiClientFlags)0/*AVAHI_CLIENT_NO_FAIL*/,FreyaAvahiHandler::wrap_client_callback,this,&error);

    /* Check the error return code */
    if(this->client != NULL && avahi_client_get_state(this->client) != AVAHI_CLIENT_CONNECTING)
    {
        g_message("Doing init");
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
        check_client_error("Initializing Avahi");
        delete this->window;
        this->window = NULL;
    }
    g_message("Exit.");
}

/* DTor */
FreyaAvahiHandler::~FreyaAvahiHandler(void)
{
    if(this->window != NULL)
        delete this->window;

    if(this->client != NULL)
        avahi_client_free(this->client);

    if(this->glib_poll != NULL)
        avahi_glib_poll_free(this->glib_poll);
}

/* For testing purpose..  */
FreyaAvahiView& FreyaAvahiHandler::get_window(void)
{
    return *(this->window);
}

/* Check if this browser has a working connection */
bool FreyaAvahiHandler::is_connected(void)
{
    return !(this->window == NULL);
}
        
sigc::signal<void,Glib::ustring,Glib::ustring,Glib::ustring, unsigned int>& FreyaAvahiHandler::get_signal(void)
{
    return this->window->signal_select;
}
