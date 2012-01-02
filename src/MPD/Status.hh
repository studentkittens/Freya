/***********************************************************
* This file is part of Freya
* - A free MPD Gtk3 MPD Client -
*
* Authors: Christopher Pahl, Christoph Piechula,
*          Eduard Schneider, Marc Tigges
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
#ifndef FREYA_MPD_STATUS
#define FREYA_MPD_STATUS

#include <mpd/client.h>

namespace MPD
{
    typedef enum mpd_state mpd_state;

    /**
     * @brief A Wrapper for mpd_status
     */
    class Status
    {
    public:

        Status(mpd_status& status,unsigned long nextSongID);
        ~Status(void);

        /* -------- */

        /**
         * @brief Get volume 0-100
         *
         * @return
         */
        int get_volume(void);
        /**
         * @brief True if on repeat mode
         *
         * @return
         */
        bool get_repeat(void);
        /**
         * @brief True if on random mode
         *
         * @return
         */
        bool get_random(void);
        /**
         * @brief True if on single mode
         *
         * @return
         */
        bool get_single(void);
        /**
         * @brief True if on consume mode
         *
         * @return
         */
        bool get_consume(void);
        /**
         * @brief Return the length of the queue (0 to UINT_MAX)
         *
         * @return
         */
        unsigned get_queue_length(void);
        /**
         * @brief The version of the Queue, starting from 0
         *
         * This is used for the plchanged command,
         * to only list the changes the versions since XYZ
         *
         * @return
         */
        unsigned get_queue_version(void);
        /**
         * @brief State of the Playback, MPD_STATE_PAUSE,_PLAY...
         *
         * @return
         */
        mpd_state get_state(void);
        /**
         * @brief Crossfade in seconds
         *
         * @return
         */
        unsigned get_crossfade(void);
        /**
         * @brief Intelligent blending treshold
         *
         * @return
         */
        float get_mixrampdb(void);
        /**
         * @brief Intelligent blending delay
         *
         * @return
         */
        float get_mixrampdelay(void);
        /**
         * @brief Song position in the queue of the currently playing song
         *
         * @return
         */
        int get_song_pos(void);
        /**
         * @brief Database ID of the current playing song
         *
         * @return
         */
        int get_song_id(void);
        /**
         * @brief Elapsed time in seconds of the current song
         *
         * @return
         */
        unsigned get_elapsed_time(void);
        /**
         * @brief Elapsed time in milliseconds of the currently playing song (higher resolution)
         *
         * @return
         */
        unsigned get_elapsed_ms(void);
        /**
         * @brief Total time of the current song in seconds
         *
         * @return
         */
        unsigned get_total_time(void);
        /**
         * @brief Current kbit rate.
         *
         * @return
         */
        unsigned get_kbit_rate(void);
        /**
         * @brief Update ID, or 0 if no updates running
         *
         * @return
         */
        unsigned get_update_id(void);
        /**
         * @brief Any error message, you dont need to use this
         *
         * @return
         */
        const char * get_error(void);
        /**
         * @brief Current sample rate
         *
         * @return
         */
        uint32_t get_audio_sample_rate(void);
        /**
         * @brief Used audio bits
         *
         * @return
         */
        uint8_t get_audio_bits(void);
        /**
         * @brief Used audio channels (Currently only Stereo or Mono)
         *
         * @return
         */
        uint8_t get_audio_channels(void);

    private:

        mpd_status * m_Status;
    };
}

#endif
