#ifndef FREYA_ABSTRACT_FILEBROWSER_GUARD
#define FREYA_ABSTRACT_FILEBROWSER_GUARD

#include "MPD/Song.hh"
#include "MPD/Directory.hh"

class AbstractFilebrowser
{
    public:

        /**
         * @brief Override this
         *
         * @param song
         *
         * @return 
         */
        virtual void add_song_file(MPD::Song * item) = 0; 
        virtual void add_directory(MPD::Directory * item) = 0; 
};

#endif
