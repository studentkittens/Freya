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
#ifndef FREYA_SONG_GUARD
#define FREYA_SONG_GUARD

#include "mpd/client.h"
#include "AbstractComposite.hh"
#include <glibmm.h>
namespace MPD
{
    typedef struct mpd_song mpd_song;

    /**
     * @brief A wrapper for mpd_song
     */
    class Song : public AbstractComposite
    {
    public:
        /**
         * @brief You are not supposed to instance this yourself.
         *
         * @param song
         */
        Song(const mpd_song& song);
        /**
         * @brief Copy Ctor
         *
         * @param other
         */
        Song(const MPD::Song& other);
        ~Song();

        /**
         * @brief The path of the song in the DB
         *
         * @return
         */
        const char * get_path();
        /**
         * @brief Get a certain tag from the song
         *
         * use song_format() if you just want a easy way to convert
         * a MPD::Song to a nice string.
         *
         * @param type The typ of the tag
         * @param idx some tags might have more than values, use this to index it, starting with 0
         *
         * @return a string
         */
        const char * get_tag(enum mpd_tag_type type, unsigned idx);
        /**
         * @brief Formats the data of the song into a string
         *
         * You can use the following formatting strings inside format
         *   - artist
         *   - title
         *   - album
         *   - track
         *   - name
         *   - data
         *   - album_artist
         *   - genre
         *   - composer
         *   - performer
         *   - comment
         *   - disc
         *
         * Each of these values should be placed inside ${fill_tagtype_in_here},
         * If the tagtype is not known, it gets not escaped, if the tag is empty,
         * it is escaped with "unknown".
         *
         * If markup ist set the string gets already markup'd for use in Gtk Widgets.
         *
         * @param format The format prototype
         * @param markup if markup should be done (see Glib::Markup::escape())
         *
         * @return the ready formatted string
         */
        Glib::ustring song_format(const char* format, bool markup=true);
        /**
         * @brief Get duratin of song in seconds
         *
         * @return
         */
        unsigned get_duration();
        /**
         * @brief Get seconds since last modifieGet seconds since last modifieff
         *
         * @return time_t type (unsigned long)
         */
        time_t get_last_modified();
        /**
         * @brief Set the position in the queue
         *
         * This is not a client command,
         * and it is not used in Freya.
         *
         * @param pos the new pos
         */
        void set_pos(unsigned pos);
        /**
         * @brief Get the position of the Song in the Queue
         *
         * @return
         */
        unsigned get_pos();
        /**
         * @brief Get Database ID of the Song
         *
         * @return
         */
        unsigned get_id();

    private:
        mpd_song * mp_Song;
        static const char unknown_tag[];
    };
}

#endif
