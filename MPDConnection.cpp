#include <glibmm.h>

#include <mpd/client.h>
#include <mpd/status.h>
#include <mpd/entity.h>
#include <mpd/search.h>
#include <mpd/tag.h>

#include <cstdlib>
#include <cstdio>
#include <iostream>

#include "MPDConnection.hpp"

using namespace std;

//-------------------
  
MPDConnection::MPDConnection()
{
    this->mpd_con = NULL;

    // Initialize GLib's threading system
    if(!Glib::thread_supported())
    {
        Glib::thread_init();
    }
    else
    {
        cerr << "FATAL: Threading is not supported on your system." << endl;
    }

    this->polling_object = NULL;
}

//-------------------

MPDConnection::~MPDConnection()
{
    //this->disconnect();
}

//-------------------

bool MPDConnection::connect(const char * hostname, unsigned int port, unsigned int timeout_ms)
{
    bool result = false;

    // Free a previously opened connection
    if(this->mpd_con == NULL)
    {
        // Try to connect to the server
        this->mpd_con = mpd_connection_new(hostname, port, timeout_ms);

        if(mpd_connection_get_error(this->mpd_con) == MPD_ERROR_SUCCESS)
        {
            const unsigned * version_tupel = mpd_connection_get_server_version(this->mpd_con);

            g_print("- libmpdclient version is %d.%d.%d\n",
                    LIBMPDCLIENT_MAJOR_VERSION,
                    LIBMPDCLIENT_MINOR_VERSION,
                    LIBMPDCLIENT_PATCH_VERSION
                    );

            g_print("- Connected with MPD Server (Server-version %d.%d.%d)\n",
                    version_tupel[0],
                    version_tupel[1],
                    version_tupel[2]);

            std::cout << "- Starting polling thread." << std::endl;
            this->polling_object = new PollingThread(this->mpd_con);
            result = true;
            Glib::usleep(100);
        }
        else
        {
            cerr << "Cannot establish connection to MPD: " << mpd_connection_get_error_message(mpd_con) << endl;
            mpd_connection_free(this->mpd_con);
            this->mpd_con = NULL;
        }
    }
    return result;
}

//-------------------

bool MPDConnection::connect()
{
    this->connect("localhost",0,3000);
}

//-------------------

void MPDConnection::disconnect()
{
    if(this->mpd_con != NULL)
    {   
        /* Tell the thread to stop */
        this->polling_object->finish();
        delete this->polling_object;
        this->polling_object = NULL;

        mpd_connection_free(mpd_con);
        this->mpd_con = NULL;
    }
}

//-------------------
