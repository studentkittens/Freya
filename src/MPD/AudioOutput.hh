#ifndef FREYA_AUDIOOUTPUT_GUARD
#define FREYA_AUDIOOUTPUT_GUARD

#include "Client.hh"

namespace MPD
{
    typedef struct mpd_output mpd_output;

    class AudioOutput
    {
        public:
            AudioOutput(MPD::Connection& conn, mpd_output * output);
            unsigned get_id(void);
            const char * get_name(void);
            bool get_enabled(void);
            bool enable(void);
            bool disable(void);

        private:
            mpd_output * mp_Output;
            MPD::Connection * mp_Conn;
    };
}

#endif /* end of include guard: FREYA_AUDIOOUTPUT_GUARD */
