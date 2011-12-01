#ifndef FREYA_NOTIFY_MANAGER_GUARD
#define FREYA_NOTIFY_MANAGER_GUARD

#include "AbstractGElement.hh"
#include "../Notify/Notify.hh"

namespace GManager
{
    class NotifyManager : public AbstractGElement
    {
        public:
            NotifyManager(MPD::Client& client);

        private:

            void on_client_update(enum mpd_idle event, MPD::NotifyData& data);
            void on_connection_change(bool is_connected);
    };
}

#endif /* end of include guard: FREYA_NOTIFY_MANAGER_GUARD */
