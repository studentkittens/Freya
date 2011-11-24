#ifndef INIT_SP0811FS

#define INIT_SP0811FS
#include <glib.h>
#include <cstring>
#include <glibmm.h>
#include <glib.h>
#include <glib/gstdio.h>
class init
{
public:
    init ();
    ~init ();
    Glib::ustring get_config_dir();
    void dir_is_avaiable();
    void create_dir();
private:
    /* data */
};

#endif /* end of include guard: INIT_SP0811FS */
