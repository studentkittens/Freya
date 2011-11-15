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
    class Heartbeat
    {
        public:

            Heartbeat(MPD::Client& client);
            ~Heartbeat(void);

        private:

            EventNotifier signal_proxy;
    };
}

#endif
