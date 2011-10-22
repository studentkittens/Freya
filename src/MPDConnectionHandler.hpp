#ifndef FREYA_MPDCLIENT_GUARD
#define FREYA_MPDCLIENT_GUARD

#include "includes.hpp"
#include "IdleListener.hpp"
#include "MPDConnection.hpp"

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
    gboolean idle_reconnect(void);

    /* Tries to handle few errors or 
     * check_error() - like lost connection
     */
    void handle_errors(enum mpd_error err);

    /* ------------------ */

    /* A IdleListener that may be attached to this Client
     * Since there will be only one a 'real' Observer is
     * pointless here.
     * */
    IdleListener * listener;

    /* The connection from libmpdclient to MPD
     */
    MPDConnection * conn;
};

#endif
