#ifndef FREYA_ABSTRACT_SONGLIST_GUARD
#define FREYA_ABSTRACT_SONGLIST_GUARD

class AbstractSonglist
{
    public:

        /**
         * @brief Override this
         *
         * @param song
         *
         * @return 
         */
        virtual bool add_item(void * item) = 0; 
        /**
         * @brief Clear all
         */
        virtual void clear(void) = 0;
};

#endif
