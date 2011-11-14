#ifndef FREYA_STATISTICS_GUARD
#define FREYA_STATISTICS_GUARD

#include <mpd/client.h>

namespace MPD
{
    typedef struct mpd_stats mpd_stats;

    class Statistics
    {
        public:

            Statistics(mpd_stats& stats);
            ~Statistics(void);

            unsigned get_number_of_artists(void);
            unsigned get_number_of_albums(void);
            unsigned get_number_of_songs(void);
            unsigned long get_uptime(void);
            unsigned long get_db_update_time(void);
            unsigned long get_play_time(void);
            unsigned long get_db_play_time (void);

        private:

            mpd_stats * mp_Statistics;
    };
}

#endif
