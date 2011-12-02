#ifndef FREYA_MPDCONNECTION_GUARD
#define FREYA_MPDCONNECTION_GUARD

#include "../includes.hh"

namespace MPD
{
    class Connection
    {
        public:

            /* Publicinstance */
            Connection(void);
            ~Connection(void);

            /* Init */
            bool is_connected(void);
            bool connect(void);
            bool disconnect(void);
            void clear_error(void);

            /* Returns mpd_conn */
            mpd_connection * get_connection(void);

        private:

            /* The connection from libmpdclient to MPD
            */
            mpd_connection * conn;
    };

}

#endif
