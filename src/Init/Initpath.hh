#ifndef INIT_SP0811FS

#define INIT_SP0811FS
#include <glibmm.h>
#include <glib/gstdio.h>
class Initpath
{
public:
    Initpath ();
    ~Initpath ();
    Glib::ustring get_config_dir();
    Glib::ustring path_to_config();

private:
    void create_config();
    void create_dir();
    void dir_is_avaiable();
};

#endif /* end of include guard: INIT_SP0811FS */
