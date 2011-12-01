#ifndef INIT_SP0811FS

#define INIT_SP0811FS
#include <glibmm.h>
#include <glib/gstdio.h>
namespace Init
{

    class Path
    {
    public:
        Path ();
        ~Path ();
        
        /**
         * @brief returns absolute path to config dir e.g. /home/user/.config/freya
         *
         * @return config dir path as ustring
         */
        Glib::ustring get_config_dir();


        /**
         * @brief returns absolute path to config file e.g. /home/user/.config/freya/config.xml
         *
         * @return config file path as ustring
         */
        Glib::ustring path_to_config();


        /**
         * @brief returns absolute path log file e.g. ~/.config/freya/log.txt
         *
         * @return log file path as ustring
         */
        Glib::ustring path_to_log();

    private:
        void create_config();
        void create_dir();
        void dir_is_avaiable();
        char* configfile;
        char* configdir;
    };
}
#endif /* end of include guard: INIT_SP0811FS */
