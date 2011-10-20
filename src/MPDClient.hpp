#ifndef FREYA_MPDCLIENT_GUARD
#define FREYA_MPDCLIENT_GUARD

#include "includes.hpp"
#include "IdleListener.hpp"

typedef struct mpd_connection mpd_connection;

class MPDClient
{
    /* Be my friend - dear Listener */
    friend class IdleListener;

    public:
    /* Publicinstance */
    MPDClient();
    ~MPDClient();

    /* Init */
    bool connect(void);
    bool disconnect(void);

    mpd_connection * mpd_conn;

    private:
    /* Instancemethods */

    /* Returns mpd_conn */
    mpd_connection * get_connection(void);

    /* Checks errors and logs them */
    bool check_error(void);

    /* ------------------ */

    /* A IdleListener that may be attached to this Client
     * Since there will be only one a 'real' Observer is
     * pointless here.
     * */
    IdleListener * idle_observer;

    /* The connection from libmpdclient to MPD
     */
};

#endif
