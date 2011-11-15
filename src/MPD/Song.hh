#ifndef FREYA_SONG_GUARD
#define FREYA_SONG_GUARD

#include "mpd/client.h"

namespace MPD
{
    typedef struct mpd_song mpd_song;

    class Song
    {
        public:
            Song(mpd_song& song);
            ~Song(void);

            const char * get_uri(void);
            const char * get_tag(enum mpd_tag_type type, unsigned idx);
            unsigned get_duration(void);
            time_t get_last_modified(void);
            void set_pos(unsigned pos);
            unsigned get_pos(void);
            unsigned get_id(void);

        private:
            mpd_song * mp_Song;
    };
}

#endif
