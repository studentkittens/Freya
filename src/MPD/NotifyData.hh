#ifndef FREYA_NOTIFYDATA_GUARD
#define FREYA_NOTIFYDATA_GUARD

#include "Connection.hh"
#include "Status.hh"
#include "Statistics.hh"

namespace MPD
{
    class NotifyData
    {
        public:
            NotifyData(Connection& conn);
            ~NotifyData(void);

            void update_status(void);
            Status& get_status(void);
    
            void update_statistics(void);
            Statistics& get_statistics(void);

        private:
            Connection * mp_Conn;
            Status * mp_Status;
            Statistics * mp_Statistics;
    };
}

#endif
