#include <glibmm.h>

#include <mpd/client.h>
#include <mpd/status.h>
#include <mpd/entity.h>
#include <mpd/search.h>
#include <mpd/tag.h>

#include <cstdlib>
#include <cstdio>
#include <iostream>

#include "PollingThread.hpp"

class MPDConnection
{
    public:
    MPDConnection();
    ~MPDConnection();

    struct mpd_connection * get_conn();
    bool connect(const char * hostname, unsigned int port, unsigned int timeout_ms);
    bool connect();
    void disconnect();

    private:
    struct mpd_connection * mpd_con; 
    PollingThread * polling_object;
};
