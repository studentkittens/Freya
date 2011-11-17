#ifndef FREYA_HEARTBEAT_GUARD
#define FREYA_HEARTBEAT_GUARD

#include "../MPD/Client.hh"

/* Explanation:
 * This class listens on the Client to get player signals, 
 * additionally it emits a signal every 500ms, for widgets
 * like the statusbar. In short: it is some sort of signalproxy
 */

namespace GManager 
{
    class ClientTimerProxy 
    {
        public:

            ClientTimerProxy(MPD::Client& client);
            ~ClientTimerProxy(void);
            EventNotifier& get_notify(void); 

        private:

            void on_client_update(enum mpd_idle event, MPD::NotifyData& data);
            gboolean on_interval(void);

            EventNotifier signal_proxy;
            MPD::Client * mp_Client;

            enum mpd_idle mp_Event;
            MPD::NotifyData * mp_Data;
    };
}

#endif
