#ifndef FREYA_NP_UPDATEINTERFACE_HH
#define FREYA_NP_UPDATEINTERFACE_HH

#include "../../MPD/Client.hh"

namespace Browser
{
    /**
     * @brief Very similar to AbstractClientUser, but doesnt take a Client instance
     */
    class UpdateInterface
    {
        public:
            virtual void update(MPD::Client& client, mpd_idle event, MPD::NotifyData& data) = 0;
    };
}

#endif /* end of include guard: FREYA_NP_UPDATEINTERFACE_HH */

