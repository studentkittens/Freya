#ifndef FREYA_SIGNALHANDLER_HH
#define FREYA_SIGNALHANDLER_HH

#include <signal.h>

namespace Init
{
    class SignalHandler
    {
        public:
            SignalHandler(void);

        private:
            struct sigaction sa_struct;
    };
}

#endif /* end of include guard: FREYA_SIGNALHANDLER_HH */

