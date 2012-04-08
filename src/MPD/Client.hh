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
#ifndef FREYA_CLIENT_GUARD
#define FREYA_CLIENT_GUARD

#include  "BaseClient.hh"

/* Songlist interface */
#include "AbstractItemGenerator.hh"

namespace MPD
{
/**
 * @brief The client implements concrete commands of the MPD Protocol
 */
class Client : public BaseClient, public AbstractItemGenerator
{
public:

    /**
     * @brief Instance the client
     *
     * If settings.connection.autoconnect is set to true
     * This also connects already anc calls force_update()
     * Use is_connected() to check if beign connected.
     */
    Client();

    /**
     * @brief Disconnects also.
     */
    ~Client();

    /**
     * @brief Connect to the MPD Server specified in the config
     *
     * See also #BaseClient
     */
    void connect();
    /**
     * @brief Disconnects from the currently connected server
     *
     * If already disconnected it does plain nothing.
     * If connection was lost violently #BaseClient will try to
     * periodically reconnect.
     */
    void disconnect();

    /**
     * @brief Go to next song
     *
     * @return true on success
     */
    bool playback_next();
    /**
     * @brief Go the prev song
     *
     * @return true on success
     */
    bool playback_prev();
    /**
     * @brief Stop playback
     *
     * Will remember the current song.
     * You have to call playback_play() to "unstop"
     *
     * @return true on success
     */
    bool playback_stop();
    /**
     * @brief Resume from stopmode
     *
     * @return true on success
     */
    bool playback_play();
    /**
     * @brief Toggle pause-state
     *
     * When playing it gets paused,
     * when being paused it starts playing.
     *
     * @return true on success
     */
    bool playback_pause();

    /**
     * @brief Seek forward in song song_id, to abs_time from start
     *
     * @param song_id The song to seek in
     * @param abs_time Time in seconds starting from 0
     */
    void playback_seek(unsigned song_id, unsigned abs_time);
    /**
     * @brief Set blending between songs in seconds
     *
     * @param seconds
     */
    void playback_crossfade(unsigned seconds);

    /**
     * @brief Toggle randome mode
     */
    void toggle_random();
    /**
     * @brief Toggle consume mode (song gets deleted from playlist after playing)
     */
    void toggle_consume();
    /**
     * @brief Toggle repeat mode (repeat playlist)
     */
    void toggle_repeat();
    /**
     * @brief Toggle single mode (stops playing after one song)
     */
    void toggle_single();

    /**
     * @brief Play song at ID (not the Pos in the Queue!)
     *
     * @param song_id
     */
    void play_song_at_id(unsigned song_id);
    /**
     * @brief Save the current queue as playlist of name @name
     *
     * @param name
     */
    void playlist_save(const char * name);

    /**
     * @brief Add song from the database to the queue
     *
     * @param url a path to the song, does not start with /
     */
    void queue_add(const char * url);
    /**
     * @brief Clears entire queue
     */
    void queue_clear();
    /**
     * @brief Deletes song in the queue
     *
     * @param pos
     */
    void queue_delete(unsigned pos);

    /**
     * @brief Update the database
     *
     * Add new files to mpd's database
     *
     * @param path a certain path, or "/" for everything
     *
     * @return an update id
     */
    unsigned database_update(const char * path);
    /**
     * @brief Full rescan of the database
     *
     * This is a very expensive operation and might take some time.
     *
     * @param path an optional path, "/" means everything.
     *
     * @return an update id
     */
    unsigned database_rescan(const char * path);

    /**
     * @brief set the volume
     *
     * @param vol Must be in [0-100]
     */
    void set_volume(unsigned vol);

    /**
     * @brief Fetches the playlist from the mpd server
     *
     * @param data_model A user defined class, that inherits from AbstractSonglist
     *
     * @return the number of filled items.
     */
    void fill_queue(AbstractItemlist& data_model);
    /**
     * @brief
     *
     * @param data_model A user defined class, that inherits from AbstractSonglist
     * @param last_version The changes since this version
     * @param first_pos The position of the song that changed first is stored here
     */
    void fill_queue_changes(AbstractItemlist& data_model, unsigned last_version, unsigned& first_pos);
    /**
     * @brief Fetches all playlists from the server
     *
     * @param data_model A user defined class, that inherits from AbstractSonglist
     */
    void fill_playlists(AbstractItemlist& data_model);
    /**
     * @brief  Fetches all available outputs from the server
     *
     * @param data_model A user defined class, that inherits from AbstractSonglist
     */
    void fill_outputs(AbstractItemlist& data_model);
    /**
     * @brief Fetches a list of files in the database
     *
     * @param data_model A user defined class, that inherits from AbstractSonglist
     * @param path A certain path, or NULL which will add /
     */
    void fill_filelist(AbstractItemlist& data_model, const char * path);

    /**
     * @brief Send a command to the server
     *
     * The output will be printed in the cmd,
     * it is therefore just useful for debugging purpose
     *
     * @param command See the protocol reference: http://www.musicpd.org/doc/protocol/index.html
     *
     * @return true on succesfull execution
     */
    bool send_command(const char * command);

    /**
     * @brief Pings server
     *
     * @return true if it responds correctly
     */
    bool ping();
};

}

#endif
