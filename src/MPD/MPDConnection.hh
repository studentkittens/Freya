#ifndef FREYA_MPDCONNECTION_H
#define FREYA_MPDCONNECTION_H

#include "../includes.hh"

class MPDConnection
{
    public:

    MPDConnection();

    /* [g|s]et connection */
    mpd_connection * get_connection(void);
    void set_connection(mpd_connection * conn);

    /* [g|s]et status */
    struct mpd_status * get_status(void);
    void set_status(struct mpd_status * status);

    /* Check if being connected */
    bool is_connected(void);

    /* The data itself */   
    private:
    mpd_status * status;
    mpd_connection * conn;
};

#endif
