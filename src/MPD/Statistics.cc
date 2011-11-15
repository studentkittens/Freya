#include "Statistics.hh"

namespace MPD
{
    Statistics::Statistics(mpd_stats& statistics)
    {
        mp_Statistics = &statistics;
    }

    Statistics::~Statistics(void)
    {
        mpd_stats_free(mp_Statistics);
    }

    unsigned Statistics::get_number_of_artists(void)
    {
        return mpd_stats_get_number_of_artists(mp_Statistics);
    }

    unsigned Statistics::get_number_of_albums(void)
    {
        return mpd_stats_get_number_of_albums(mp_Statistics);
    }

    unsigned Statistics::get_number_of_songs(void)
    {
        return mpd_stats_get_number_of_songs(mp_Statistics);
    }

    unsigned long Statistics::get_uptime(void)
    {
        return mpd_stats_get_uptime(mp_Statistics);
    }

    unsigned long Statistics::get_db_update_time(void)
    {
        return mpd_stats_get_db_update_time(mp_Statistics);
    }

    unsigned long Statistics::get_play_time(void)
    {
        return mpd_stats_get_play_time(mp_Statistics);
    }

    unsigned long Statistics::get_db_play_time (void)
    {
        return mpd_stats_get_db_play_time(mp_Statistics);
    }
}
