#include "Status.hh"

namespace MPD
{
    Status::Status(mpd_status& status, unsigned long nextSongID)
    {
        m_Status = &status;
    }

    Status::~Status(void)
    {
        mpd_status_free(m_Status);
    }

    int Status::get_volume(void)
    {
        return mpd_status_get_volume(m_Status);
    }

    bool Status::get_repeat(void)
    {
        return mpd_status_get_repeat(m_Status);
    }

    bool Status::get_random(void)
    {
        return mpd_status_get_random(m_Status);
    }

    bool Status::get_single(void)
    {
        return mpd_status_get_single(m_Status);
    }

    bool Status::get_consume(void)
    {
        return mpd_status_get_consume(m_Status);
    }

    unsigned Status::get_queue_length(void)
    {
        return mpd_status_get_queue_length(m_Status);
    }

    unsigned Status::get_queue_version(void)
    {
        return mpd_status_get_queue_version(m_Status);
    }

    mpd_state Status::get_state(void)
    {
        return mpd_status_get_state(m_Status);
    }

    unsigned Status::get_crossfade(void)
    {
        return mpd_status_get_crossfade(m_Status);
    }

    float Status::get_mixrampdb(void)
    {
        return mpd_status_get_mixrampdb(m_Status);
    }

    float Status::get_mixrampdelay(void)
    {
        return mpd_status_get_mixrampdelay(m_Status);
    }

    int Status::get_song_pos(void)
    {
        return mpd_status_get_song_pos(m_Status);
    }

    int Status::get_song_id(void)
    {
        return mpd_status_get_song_id(m_Status);
    }

    unsigned Status::get_elapsed_time(void)
    {
        return mpd_status_get_elapsed_time(m_Status);
    }

    unsigned Status::get_elapsed_ms(void)
    {
        return mpd_status_get_elapsed_ms(m_Status);
    }

    unsigned Status::get_total_time(void)
    {
        return mpd_status_get_total_time(m_Status);
    }

    unsigned Status::get_kbit_rate(void)
    {
        return mpd_status_get_kbit_rate(m_Status);
    }

    unsigned Status::get_update_id(void)
    {
        return mpd_status_get_update_id(m_Status);
    }

    const char * Status::get_error(void)
    {
        return mpd_status_get_error(m_Status);
    }

    uint32_t Status::get_audio_sample_rate(void)
    {
        const mpd_audio_format * fmt = mpd_status_get_audio_format(m_Status);
        uint32_t sample_rate = (fmt == NULL) ? -1 : fmt->sample_rate;

        /* This is a poor fix for the obviously wrong return values from mpd 
         * Returns INT_MAX (1 << 32) sometimes for some reason. */
        return (sample_rate > (uint32_t)(1 << 31)) ? 44100 : sample_rate;
    }

    uint8_t Status::get_audio_bits(void)
    {
        const mpd_audio_format * fmt = mpd_status_get_audio_format(m_Status);
        return (fmt == NULL) ? -1 : fmt->bits;
    }

    uint8_t Status::get_audio_channels(void)
    {
        const mpd_audio_format * fmt = mpd_status_get_audio_format(m_Status);
        return (fmt == NULL) ? -1 : fmt->channels;
    }
}
