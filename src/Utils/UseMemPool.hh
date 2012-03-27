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

        /* 
         * WARNING: This only works fine when real slice allocation can be used.
         *          If g_malloc() is used freeing memory will cause weird beahviour / memory leaks.
         *          Memory allocation can be influenced by the G_SLICE Env variable.
         */
        static void prealloc(size_t n_iterations = 128)
        {
            gsize memsize = sizeof(StorageClass) * n_iterations;
            gpointer memdata = g_slice_alloc(memsize);

            for(unsigned off = 0; off < memsize; off += sizeof(StorageClass))
                operator delete (((char*)memdata) + off);
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
