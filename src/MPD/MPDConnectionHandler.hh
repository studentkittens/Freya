#ifndef FREYA_MPDCONNECTION_GUARD
#define FREYA_MPDCONNECTION_GUARD

#include "../includes.hh"
#include "IdleListener.hh"

/* Prototype class */
class IdleListener;

class MPDConnectionHandler
{
    /* Be my friend - dear Listener */
    friend class IdleListener;

    public:

    /* Publicinstance */
    MPDConnectionHandler();
    ~MPDConnectionHandler();

    /* Init */
    bool connect(void);
    bool disconnect(void);
    bool is_connected(void);

    /* Returns mpd_conn */
    mpd_connection * get_connection(void);

    /* Returns listener */
    IdleListener * get_listener(void);

    /* Checks errors and logs them */
    bool check_error(void);

    private:

    /* A callback that is called by the MainLoop,
     * if the connection was lost - if so it tries
     * to reconnect
     */
    gboolean timeout_reconnect(void);

    void handle_errors(enum mpd_error err);

    /* A IdleListener that may be attached to this Client
     * Since there will be only one a 'real' Observer is
     * pointless here.
     * */
    IdleListener * listener;

    /* The connection from libmpdclient to MPD
     */
    mpd_connection * conn;
    mpd_status * current_status;
};

#endif
