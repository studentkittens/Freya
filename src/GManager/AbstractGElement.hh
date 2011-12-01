#ifndef FREYA_ABSTRACT_GELEMENT_GUARD
#define FREYA_ABSTRACT_GELEMENT_GUARD

#include "../MPD/Client.hh"

namespace GManager
{
    class AbstractGElement 
    {
        public:
            AbstractGElement(MPD::Client& client)
            {
                /* Save a ref. to the client */
                mp_Client = &client;

                /* Connect to client changes */
                client.get_notify().connect(sigc::mem_fun(*this,
                            &AbstractGElement::on_client_update));
                
                /* Connect to connection change */
                client.signal_connection_change().connect(sigc::mem_fun(
                            *this,&AbstractGElement::on_connection_change));
            }

        protected:

            /* You have to implement both of these functions. */
            virtual void on_client_update(enum mpd_idle, MPD::NotifyData& data) = 0;
            virtual void on_connection_change(bool is_connected) = 0;

            /* Setting the client is error-prone. This class does this for you. */
            MPD::Client * mp_Client;
    };
} 

#endif /* end of include guard: FREYA_BASEGELEMENT_GUARD */
