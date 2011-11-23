#include <stdio.h>
#include <glib.h>
#include <stdlib.h>
#include "init.hh"

init::init()
{}

init::~init()
{}

Glib::ustring init::get_config_dir()
{
    Glib::ustring retv = g_strdup_printf("%s%s",g_get_user_config_dir(),"/freya");
    printf("%s\n",retv.c_str());
    return retv;
}


void init::dir_is_avaiable()
{

    if (g_file_test(get_config_dir().c_str(), G_FILE_TEST_EXISTS ))
        printf("ja es ist da\n");
    else
    {
        printf("nein es ist nicht da\n");
        create_dir();
    }
}

void init::create_dir()
{
    g_mkdir(get_config_dir().c_str(),0755);
}

