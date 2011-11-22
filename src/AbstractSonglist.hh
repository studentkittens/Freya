#ifndef FREYA_ABSTRACT_SONGLIST_GUARD
#define FREYA_ABSTRACT_SONGLIST_GUARD

#include "MPD/Song.hh"

class AbstractSonglist
{
    public:

        /**
         * @brief Tell BrowserList which element to manage 
         *
         * You are supposed to override this.
         *
         * @return A reference to the containing widget of the browser 
         */
        virtual bool add_song(MPD::Song * song) = 0; 
};

#endif
