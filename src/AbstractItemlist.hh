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
};

#endif
