#ifndef FREYA_NOTIFYDATA_GUARD
#define FREYA_NOTIFYDATA_GUARD

#include "Connection.hh"
#include "Statistics.hh"
#include "Status.hh"
#include "Song.hh"

namespace MPD
{
    class NotifyData
    {
        public:
            NotifyData(Connection& conn);
            ~NotifyData(void);

            Status& get_status(void);
            Statistics& get_statistics(void);
            Song& get_song(void);
            Song& get_next_song(void);

            /**
             * @brief Update internal client state
             */
            void update_all(void);

        private:

            /**
             * @brief Custom implementation of mpd_run_status()
             *
             * @return same as mpd_run_status(), but sets m_NextSongID
             */
            Status * recv_status_own(void);
            
            /**
             * @brief Current valid connection.
             */
            Connection * mp_Conn;

            /**
             * @brief The mpd status (wrapped to C++ object)
             */
            Status * mp_Status;
            /**
             * @brief MPD statistics (wrapped to C++ object)
             */
            Statistics * mp_Statistics;
            /**
             * @brief Currently playing song (wrapped to C++ object)
             */
            Song * mp_Song;
            Song * mp_NextSong;
    };
}

#endif
