#ifndef FREYA_USEMEMPOOL_HH
#define FREYA_USEMEMPOOL_HH

#include <glib.h>
#include <algorithm>

template<class StorageClass> 
class UseMemPool 
{
    public:

        void * operator new(size_t size)
        {
            g_assert(size >= sizeof(gpointer));

            gpointer mem = NULL;
            if((mem = g_trash_stack_pop(&memstack)) == NULL) {
                mem = g_slice_alloc(size);
            }
            return mem;
        }

        ////////////////////////////

        void operator delete(void * ptr)
        {
            g_trash_stack_push(&memstack,ptr);
        }

        ////////////////////////////

        static void disposeAll()
        {
            g_slice_free_chain(GTrashStack,memstack,next);
            memstack = NULL;
        }

        ////////////////////////////

    private:
        static GTrashStack * memstack;
}; 

template<class StorageClass> 
GTrashStack * UseMemPool<StorageClass>::memstack = NULL;

#endif /* end of include guard: FREYA_USEMEMPOOL_HH */
