#include "Playlist.hh"

namespace MPD
{
    Playlist::Playlist(mpd_playlist& playlist)
    {
        mpc_playlist = &playlist;
    }

    Playlist::Playlist(const Playlist& copy_this)
    {
        if(copy_this.mpc_playlist != NULL)
        {
            mpc_playlist = mpd_playlist_dup(copy_this.mpc_playlist);
        }
    }

    Playlist::~Playlist(void)
    {
        if(mpc_playlist != NULL)
            mpd_playlist_free(mpc_playlist);
    }

    const char * Playlist::get_path(void)
    {
        return mpd_playlist_get_path(mpc_playlist);
    }

    time_t Playlist::get_last_modified(void)
    {
        return mpd_playlist_get_last_modified(mpc_playlist);
    }
}
