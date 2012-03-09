#ifndef FREYA_NP_UPDATEINTERFACE_HH
#define FREYA_NP_UPDATEINTERFACE_HH

#include "../MPD/Client.hh"
extern "C" {
    #include <glyr/glyr.h>
}

namespace Glyr 
{
    class Stack;

    /**
     * @brief Very similar to AbstractClientUser, but doesnt take a Client instance
     */
    class UpdateInterface
    {
        friend class Glyr::Stack;

        public:

            virtual void update(MPD::Client& client, mpd_idle event, MPD::NotifyData& data) = 0;

            virtual void on_deliver(GlyrMemCache * c) {}

        private:

            void deliver_internal(GlyrMemCache * c, Glib::Dispatcher * disp)
            {
                on_deliver(c);
                delete disp;
            }

            Glib::Dispatcher resultDispatcher;
            sigc::connection dispatchConn;
    };
}

#endif /* end of include guard: FREYA_NP_UPDATEINTERFACE_HH */
