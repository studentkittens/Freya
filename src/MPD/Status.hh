#ifndef FREYA_MPD_STATUS
#define FREYA_MPD_STATUS

#include <mpd/client.h>

namespace MPD
{
    typedef enum mpd_state mpd_state;

    class Status
    {
        public: 

            Status(mpd_status& status);
            ~Status(void);

            /* -------- */

            int get_volume(void);
            bool get_repeat(void);
            bool get_random(void);
            bool get_single(void);
            bool get_consume(void);
            unsigned get_queue_length(void);
            unsigned get_queue_version(void);
            mpd_state get_state(void);
            unsigned get_crossfade(void);
            float get_mixrampdb(void);
            float get_mixrampdelay(void);
            int get_song_pos(void);
            int get_song_id(void);
            unsigned get_elapsed_time(void);
            unsigned get_elapsed_ms(void);
            unsigned get_total_time(void);
            unsigned get_kbit_rate(void);
            unsigned get_update_id(void);
            const char * get_error(void);

            uint32_t get_audio_sample_rate(void);
            uint8_t get_audio_bits(void);
            uint8_t get_audio_channels(void);

        private: 

            mpd_status * m_Status;
    };
}

#endif
