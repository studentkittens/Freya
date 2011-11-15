#include "Song.hh"

namespace MPD
{
    Song::Song(mpd_song& song)
    {
        mp_Song = &song;
    }
    
    /*------------------------------*/
    
    Song::~Song(void)
    {
        mpd_song_free(mp_Song);
    }

    /*------------------------------*/

    const char * Song::get_uri(void)
    {
        return mpd_song_get_uri(mp_Song);
    }
    /*------------------------------*/

    const char * Song::get_tag(enum mpd_tag_type type, unsigned idx)
    {
        return mpd_song_get_tag(mp_Song,type,idx);

    }
    /*------------------------------*/

    unsigned Song::get_duration(void)
    {
        return mpd_song_get_duration(mp_Song);

    }
    /*------------------------------*/

    time_t Song::get_last_modified(void)
    {
        return mpd_song_get_last_modified(mp_Song);

    }
    /*------------------------------*/

    void Song::set_pos(unsigned pos)
    {
        mpd_song_set_pos(mp_Song,pos);

    }
    /*------------------------------*/

    unsigned Song::get_pos(void)
    {
        return mpd_song_get_pos(mp_Song);

    }
    /*------------------------------*/

    unsigned Song::get_id(void)
    {
        return mpd_song_get_id(mp_Song);
    }
    /*------------------------------*/
}
