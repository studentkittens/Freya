#include <iostream>
#include <gtkmm.h>
#include "MPDConfigHandler.hh"
using namespace std;

/*main*/
int main(int argc, char *argv[])
{
    MPDConfigHandler xxx((char*)"./config.xml");
    if (argc > 1)
    {
        xxx.set_value("settings.connection.host","katze");    
        Glib::ustring& bla  = xxx.get_value((Glib::ustring)argv[1]);
        printf("%s\n",bla.c_str());
        delete &bla;
    }

    return EXIT_SUCCESS;
}
