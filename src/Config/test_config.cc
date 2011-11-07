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
    MPDConfigHandler xxx((char*)"./config.xml");
    if(!strcmp(argv[1],"set") && argc > 3)
    {
        xxx.set_value(argv[2],argv[3]);
        Glib::ustring& bla  = xxx.get_value((Glib::ustring)argv[2]);
        g_message("value = '%s'",bla.c_str());
        delete &bla;
    }
    else if(!strcmp(argv[1],"get") && argc > 2)
    {
        Glib::ustring& bla  = xxx.get_value((Glib::ustring)argv[2]);
        g_message("value = '%s'",bla.c_str());
        delete &bla;
    }
    return EXIT_SUCCESS;
}
