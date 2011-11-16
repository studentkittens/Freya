#include "Initpath.hh"
#include "../Config/Handler.hh"
#include "../Config/defaultcfg.inl"
#include <string.h>


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
            if (!g_access( path_to_config().c_str(),W_OK|R_OK))
            {
                printf("%s config avaiable and read/writeable.\n", path_to_config().c_str());
            }
            else
            {
                printf("%s config read/write permission problem.\n",path_to_config().c_str());
            }
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

    Glib::ustring path = get_config_dir()+"/config.xml";

    FILE * file;
    char* buffer = (char*)Config::defaultconfig.c_str();
    file = fopen ( (char*)path.c_str() , "w" );
    if (NULL!=file)
    {
        fwrite (buffer , 1 , strlen(buffer) , file );
        fclose (file);
        printf("config created. %s\n", path_to_config().c_str());
    }
    else
    {
        printf("AAAAAAAAAAAAAHHHHHHHHHH unable to write file!!!%s\n",path.c_str());
    }
}

void Initpath::create_dir()
{
    if (!g_mkdir_with_parents(get_config_dir().c_str(),0755))
    {
        printf("dir %s succesfully created.\n",get_config_dir().c_str());
    }
    else
    {
        perror("Cannot create ~/.config/freya");
    }
}

