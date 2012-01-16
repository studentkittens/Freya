/***********************************************************
* This file is part of Freya
* - A free MPD Gtk3 MPD Client -
*
* Authors: Christopher Pahl, Christoph Piechula,
*          Eduard Schneider
*
* Copyright (C) [2011-2012]
* Hosted at: https://github.com/studentkittens/Freya
*
*              __..--''``---....___   _..._    __
*    /// //_.-'    .-/";  `        ``<._  ``.''_ `. / // /
*   ///_.-' _..--.'_                        `( ) ) // //
*   / (_..-' // (< _     ;_..__               ; `' / ///
*    / // // //  `-._,_)' // / ``--...____..-' /// / //
*  Ascii-Art by Felix Lee <flee@cse.psu.edu>
*
* Freya is free software: you can redistribute it and/or modify
* it under the terms of the GNU General Public License as published by
* the Free Software Foundation, either version 3 of the License, or
* (at your option) any later version.
*
* Freya is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
* GNU General Public License for more details.
*
* You should have received a copy of the GNU General Public License
* along with Freya. If not, see <http://www.gnu.org/licenses/>.
**************************************************************/
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
