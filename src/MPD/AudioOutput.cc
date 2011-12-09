#include "AudioOutput.hh"

namespace MPD
{
    AudioOutput::AudioOutput(MPD::Connection& conn, mpd_output * output)
    {
        mp_Output = output;
        mp_Conn   = &conn;

        g_assert(mp_Conn);
        g_assert(output);
    }

    /* ----------------- */
    
    unsigned AudioOutput::get_id(void)
    {
        return mpd_output_get_id(mp_Output); 
    }

    const char * AudioOutput::get_name(void)
    {
        return mpd_output_get_name(mp_Output);
    }

    bool AudioOutput::get_enabled(void)
    {
        return mpd_output_get_enabled(mp_Output);
    }

    bool AudioOutput::enable(void)
    {
        unsigned id = get_id();
        return mpd_run_enable_output(mp_Conn->get_connection(),id);
    }

    bool AudioOutput::disable(void)
    {
        unsigned id = get_id();
        return mpd_run_disable_output(mp_Conn->get_connection(),id);
    }
}
