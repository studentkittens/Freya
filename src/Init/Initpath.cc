#include "Initpath.hh"
#include "../Config/Handler.hh"

Initpath::Initpath()
{
    dir_is_avaiable();
}

Initpath::~Initpath()
{}

Glib::ustring Initpath::get_config_dir()
{
    Glib::ustring retv = Glib::ustring(g_get_user_config_dir()) + (char*)"/freya";
    return retv;
}


Glib::ustring Initpath::path_to_config()
{
    Glib::ustring retv = Glib::ustring(get_config_dir().c_str() )+ (char*)"/config.xml"; 
    return retv;
}

void Initpath::dir_is_avaiable()
{
    if (g_file_test(get_config_dir().c_str(), G_FILE_TEST_EXISTS) && g_file_test(get_config_dir().c_str(), G_FILE_TEST_IS_DIR)) 
    {
        if (g_file_test(path_to_config().c_str(), G_FILE_TEST_IS_REGULAR))
        {
            printf("%s config avaiable.\n", path_to_config().c_str());
        }
        else
        {
            create_config();
        }
    }
    else 
    {
        create_dir();
        create_config();
    }
}

void Initpath::create_config()
{
        printf("config created. %s\n", path_to_config().c_str());
        Glib::ustring path = get_config_dir()+"/config.xml";
        Config::Handler::instance().write_default((char*)path.c_str());
}

void Initpath::create_dir()
{
    if (!g_mkdir(get_config_dir().c_str(),0755))
    {
        printf("dir %s succesfully created.\n",get_config_dir().c_str());
    }
    else
    {
        printf("failed to create config dir: %s\n",get_config_dir().c_str());
    }
}

