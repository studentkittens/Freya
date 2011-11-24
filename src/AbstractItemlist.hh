#ifndef FREYA_ABSTRACT_SONGLIST_GUARD
#define FREYA_ABSTRACT_SONGLIST_GUARD

class AbstractItemlist
{
    public:

        /**
         * @brief Override this
         *
         * @param song
         *
         * @return 
         */
        virtual void add_item(void * item) = 0; 

        /**
         * @brief Clear all
         */
        virtual void clear(void) = 0;
};

#endif
