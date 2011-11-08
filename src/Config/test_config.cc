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
    ConfigHandler& xxx=  ConfigHandler::instance();
    if(argc > 3 && !strcmp(argv[1],"set"))
    {
        xxx.set_value(argv[2],argv[3]);
        Glib::ustring& bla  = xxx.get_value((Glib::ustring)argv[2]);
        g_message("value = '%s'",bla.c_str());
        delete &bla;
    }
    else if(argc > 2 && !strcmp(argv[1],"get"))
    {
        Glib::ustring& bla  = xxx.get_value((Glib::ustring)argv[2]);
        g_message("value = '%s'",bla.c_str());
        delete &bla;
    }
    return EXIT_SUCCESS;
}
