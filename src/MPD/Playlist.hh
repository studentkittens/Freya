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
#ifndef FREYA_PLAYLIST_GUARD
#define FREYA_PLAYLIST_GUARD

#include <mpd/client.h>
#include "AbstractClientExtension.hh"
#include "AbstractComposite.hh"
#include "Song.hh"

namespace MPD
{
    typedef struct mpd_playlist mpd_playlist;

    /**
     * @brief A Wrapper for mpd_playlist, also implements own client commands
     */
    class Playlist : public AbstractClientExtension, public AbstractComposite
    {
    public:
        Playlist(MPD::BaseClient& base_client, mpd_playlist& c_playlist);
        Playlist(const Playlist& copy_this);
        virtual ~Playlist(void);

        /**
         * Returns the path name of this playlist file.  It does not begin
         * with a slash.
         */
        const char * get_path(void);

        /**
         * @return the POSIX UTC time stamp of the last modification, or 0 if
         * that is unknown
         */
        time_t get_last_modified(void);

        /**
         * @brief Remove this Playlist from MPD
         */
        void remove(void);

        /**
         * @brief load this playlist into the queue (add to end)
         */
        void load(void);

        /**
         * @brief Rename playlist
         *
         * @param new_name The new name as string
         */
        void rename(const char * new_name);

        /**
         * @brief Add song identified with path uri to this playlist
         *
         * @param uri a path to a song in the DB
         */
        void add_song(const char * uri);

        /**
         * @brief Add song to this playlist
         *
         * @param song a valid MPD::Song
         */
        void add_song(MPD::Song& song);

    private:
        mpd_playlist * mpc_playlist;

    };
}

#endif /* end of include guard: FREYA_PLAYLIST_GUARD */
