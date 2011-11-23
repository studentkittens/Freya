#ifndef FREYA_PLAYLIST_GUARD
#define FREYA_PLAYLIST_GUARD

#include <mpd/client.h>

namespace MPD
{
    typedef struct mpd_playlist mpd_playlist;
    class Playlist
    {
        public:
            Playlist(mpd_playlist& c_playlist);
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

        private:
            mpd_playlist * mpc_playlist;

    };
}

#endif /* end of include guard: FREYA_PLAYLIST_GUARD */
