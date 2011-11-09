#include <iostream>
#include <glibmm.h>
#include <cstring>
#include "ConfigHandler.hh"

using namespace std;

/*
 * Exammple:
 * ./bin/test_config get settings.notify.signal
 * ./bin/test_config set settings.notify.signal 2
 */

int main(int argc, char *argv[])
{
    if(argc > 3 && !strcmp(argv[1],"set"))
    {
        CONFIG_SET(argv[2],argv[3]);
        int bla  = CONFIG_GET_AS_INT(Glib::ustring(argv[2]));
        g_message("value = '%d'",bla);
    }
    else if(argc > 2 && !strcmp(argv[1],"get"))
    {
        Glib::ustring bla  = CONFIG_GET(Glib::ustring(argv[2]));
        g_message("value = '%s'",bla.c_str());
    }
    return EXIT_SUCCESS;
}
