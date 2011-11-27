#ifndef FREYA_NOTIFY_GUARD
#define FREYA_NOTIFY_GUARD

#include "../Singleton.hh"
#include <gtkmm.h>

/*----> THIS IS JUST A TEST. THIS IS NOT MEANT TO BE A REAL NOTIFICATIONSYSTEM. <----*/

namespace Notify
{
    class Notify
    {
            DEF_SINGLETON( Notify )
        public:
            ~Notify();
            void send(Glib::ustring msg);
    };
}

#define NOTIFY_SEND(x) Notify::Notify::instance().send(x)

#endif
