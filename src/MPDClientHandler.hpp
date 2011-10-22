#ifndef FREYA_MPDCLIENTHANDLER
#define FREYA_MPDCLIENTHANDLER 

#include "includes.hpp"
#include  "MPDConnectionHandler.hpp"

class MPDClientHandler
{
    public:

    MPDClientHandler();
    ~MPDClientHandler();

    /* Go to next song */
    bool send_command(const char * command);

    /* Get the underlying connection handler */
    MPDConnectionHandler * get_connection_handler(void);

    private:

    void go_idle(void);
    void go_busy(void);

    /* Get mpd_connection * from MPDClientHandler */
    mpd_connection * get_conn_by_obj(void);

    // Instancevars //

    /* The wrapped up mpd_connection */
    MPDConnectionHandler * conn;
};

#endif
