#include "Path.hh"
#include "../Config/defaultcfg.inl"
#include <string.h>

namespace Init
{
    Path::Path()
    {
        /* setting configdir member */
        configdir = g_strdup_printf("%s",(char*)get_config_dir().c_str());

        /* setting configfile member */
        configfile = g_strdup_printf("%s",(char*)path_to_config().c_str());

        dir_is_avaiable();
    }


    Path::~Path()
    {
        g_free(configdir);
        g_free(configfile);
    }


    /* return config dir path as ustring */
    Glib::ustring Path::get_config_dir()
    {
        Glib::ustring retv = Glib::ustring(g_get_user_config_dir()) + (char*)"/freya";
        return retv;
    }


    /* return path to config */
    Glib::ustring Path::path_to_config()
    {
        Glib::ustring retv = Glib::ustring(get_config_dir())+ (char*)"/config.xml";
        return retv;
    }

    /* return path to config */
    Glib::ustring Path::path_to_log()
    {
        Glib::ustring retv = Glib::ustring(get_config_dir())+ (char*)"/log.txt";
        return retv;
    }

    /*check if config dir an file is avaiable, if not, try to create */
    void Path::dir_is_avaiable()
    {
        if (g_file_test(configdir, G_FILE_TEST_EXISTS) && g_file_test(configdir, G_FILE_TEST_IS_DIR))
        {
            if (g_file_test(configfile, G_FILE_TEST_IS_REGULAR))
            {
                if (!g_access( configfile,W_OK|R_OK))
                {
                    g_message("%s config succesfully read.", configfile);
                }
                else
                {
                    g_warning("%s probably a permission problem.",configfile);
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
    void Path::create_config()
    {
        FILE * file = fopen ( configfile , "w" );
        if (NULL!=file)
        {
            fwrite(Config::defaultconfig.c_str(), 1, Config::defaultconfig.size(), file );
            fclose(file);
            g_message("config %s created.", configfile);
        }
        else
        {
            g_warning("unable to write %s.",configfile);
        }
    }


    /* creates dir for config.xml */
    void Path::create_dir()
    {
        if (!g_mkdir_with_parents(configdir,0755))
        {
            g_message("dir %s, succesfully created.",configdir);
        }
        else
        {
            g_warning("cannot create ~/.config/freya %s",strerror(errno));
        }
    }
}
