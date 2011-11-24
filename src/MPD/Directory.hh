#ifndef DIRECTORY_FY7WZEO9
#define DIRECTORY_FY7WZEO9

#include <mpd/client.h>

namespace MPD
{
    class Directory
    {
        public:
            Directory(mpd_directory& dir);
            virtual ~Directory(void);

            const char * get_path(void);

        private:

            mpd_directory * mp_Dir;
    };
}

#endif /* end of include guard: DIRECTORY_FY7WZEO9 */
