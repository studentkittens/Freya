#ifndef FREYA_NOTIFYDATA_GUARD
#define FREYA_NOTIFYDATA_GUARD

#include "Connection.hh"
#include "Status.hh"

namespace MPD
{
    class NotifyData
    {
        public:
            NotifyData(Connection& conn);
            ~NotifyData(void);

            void update_status(void);
            Status& get_status(void);

        private:
            Connection * mp_Conn;
            Status * mp_Status;
    };
}

#endif
