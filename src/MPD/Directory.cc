#include "Directory.hh"

namespace MPD
{
    Directory::Directory(mpd_directory& dir)
    {
        mp_Dir = &dir;
    }

    Directory::~Directory(void)
    {
        if(mp_Dir != NULL)
        {
            mpd_directory_free(mp_Dir);
        }
    }

    const char * Directory::get_path(void)
    {
        return mpd_directory_get_path(mp_Dir);
    }
}
