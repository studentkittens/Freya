#ifndef FREYA_SIGNALHANDLER_HH
#define FREYA_SIGNALHANDLER_HH

namespace Init
{
    /**
     * @brief By Instancing this class Signalhandlers are registered
     *
     * SIGSEGV and other crash signals are catched, so that log and
     * config can be closed properly.
     *
     * Only compiled on not windows plattforms
     */
    class SignalHandler
    {
        public:
            SignalHandler();
    };
}

#endif /* end of include guard: FREYA_SIGNALHANDLER_HH */

