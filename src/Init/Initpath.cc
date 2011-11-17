#include "Initpath.hh"
#include "../Config/Handler.hh"
#include "../Config/defaultcfg.inl"
#include <string.h>
#include "../Log/Writer.hh"

namespace Init
{

    Initpath::Initpath()
    {
        /* setting configdir member */
        configdir = g_strdup_printf("%s",(char*)get_config_dir().c_str());

        /* setting configfile member */
        configfile = g_strdup_printf("%s",(char*)path_to_config().c_str());

        dir_is_avaiable();
    }


    Initpath::~Initpath()
    {
        g_free(configdir);
        g_free(configfile);
    }


    /* return config dir path as ustring */
    Glib::ustring Initpath::get_config_dir()
    {
        Glib::ustring retv = Glib::ustring(g_get_user_config_dir()) + (char*)"/freya";
        return retv;
    }


    /* return path to config */
    Glib::ustring Initpath::path_to_config()
    {
        Glib::ustring retv = Glib::ustring(get_config_dir())+ (char*)"/config.xml";
        return retv;
    }


    /*check if config dir an file is avaiable, if not, try to create */
    void Initpath::dir_is_avaiable()
    {
        if (g_file_test(configdir, G_FILE_TEST_EXISTS) && g_file_test(configdir, G_FILE_TEST_IS_DIR))
        {
            if (g_file_test(configfile, G_FILE_TEST_IS_REGULAR))
            {
                if (!g_access( configfile,W_OK|R_OK))
                {
                    Info("%s config succesfully read.\n", configfile);
                }
                else
                {
                    Warning("%s probably a permission problem.\n",configfile);
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


    /*creates config.xml inside config dir */
    void Initpath::create_config()
    {
        FILE * file;
        char* buffer = (char*)Config::defaultconfig.c_str();
        file = fopen ( configfile , "w" );
        if (NULL!=file)
        {
            fwrite (buffer , 1 , strlen(buffer) , file );
            fclose (file);
            Success("config %s created.\n", configfile);
        }
        else
        {
            Error("unable to write %s.\n",configfile);
        }
    }


    /* creates dir for config.xml */
    void Initpath::create_dir()
    {
        if (!g_mkdir_with_parents(configdir,0755))
        {
            Success("dir %s, succesfully created.\n",configdir);
        }
        else
        {
            Error("cannot create ~/.config/freya %s",strerror(errno));
        }
    }
}

