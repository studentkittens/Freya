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

            void update_all(void);

        private:
            Connection * mp_Conn;
            Status * mp_Status;
            Statistics * mp_Statistics;
            Song * mp_Song;
    };
}

#endif
