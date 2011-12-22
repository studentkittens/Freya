#ifndef FREYA_SIGNALHANDLER_HH
#define FREYA_SIGNALHANDLER_HH

#include <signal.h>

namespace Init
{
    /**
     * @brief By Instancing this class Signalhandlers are registered
     *
     * SIGSEGV and other crash signals are catched, so that log and 
     * config can be closed properly.
     */
    class SignalHandler
    {
        public:
            SignalHandler(void);

        private:
            struct sigaction sa_struct;
    };
}

#endif /* end of include guard: FREYA_SIGNALHANDLER_HH */

