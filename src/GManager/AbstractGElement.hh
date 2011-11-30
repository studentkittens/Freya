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
                mp_Client = &client;

                client.get_notify().connect(sigc::mem_fun(*this,
                            &AbstractGElement::on_client_update));

                client.signal_connection_change().connect(sigc::mem_fun(
                            *this,&AbstractGElement::on_connection_change));
            }

        protected:
            virtual void on_client_update(enum mpd_idle, MPD::NotifyData& data) = 0;
            virtual void on_connection_change(bool is_connected) = 0;
            MPD::Client * mp_Client;
    };
} 

#endif /* end of include guard: FREYA_BASEGELEMENT_GUARD */
