#ifndef FREYA_HEARTBEAT_GUARD
#define FREYA_HEARTBEAT_GUARD

#include "../MPD/Client.hh"
#include "../AbstractClientUser.hh"

/* Explanation:
 * This class listens on the Client to get player signals, 
 * additionally it emits a signal every 500ms, for widgets
 * like the statusbar. In short: it is some sort of signalproxy
 */

typedef sigc::signal<void,double> TimerNotifier;

namespace GManager
{
    class Heartbeat : public AbstractClientUser
    {
        public:

            Heartbeat(MPD::Client& client);
            ~Heartbeat(void);
            TimerNotifier& get_notify(void); 
           
            void play(void); 
            void pause(void);
            void reset(void);
            void set(double val);
            double get(void);

        private:

            double timer;
            bool count_up;

            gboolean on_interval(void);
            TimerNotifier signal_proxy;

            void on_client_update(enum mpd_idle event, MPD::NotifyData& data);
            void on_connection_change(bool is_connected);
    };
}

#endif
