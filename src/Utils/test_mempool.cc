#include "UseMemPool.hh"

////////////////////////////////////////

class SomeClass : public UseMemPool<SomeClass>
{
    char buf[1024];
};

////////////////////////////////////////

class SomeClassWithoutMemPool
{
    char buf[1024];
};

////////////////////////////////////////

int main()
{
    double t1, t2;
    const int iterations = 500000;
    GTimer * watch = g_timer_new();
    //SomeClass::prealloc(iterations);
    g_timer_stop(watch);
    g_print("%f seconds for prealloc()\n",g_timer_elapsed(watch,NULL));
    g_timer_start(watch);
    {
        SomeClass * mem_ptr[iterations];
        for(int i = 0; i < 10; i++)
        {
            for(int i = 0; i < iterations; i++)
                mem_ptr[i]  = new SomeClass;
            for(int i = 0; i < iterations; i++)
                delete mem_ptr[i];
        }
    }
    g_timer_stop(watch);
    t1 = g_timer_elapsed(watch,NULL);
    g_timer_start(watch);
    {
        SomeClassWithoutMemPool * mem_ptr[iterations];
        for(int i = 0; i < 10; i++)
        {
            for(int i = 0; i < iterations; i++)
                mem_ptr[i]  = new SomeClassWithoutMemPool;
            for(int i = 0; i < iterations; i++)
                delete mem_ptr[i];
        }
    }
    g_timer_stop(watch);
    t2 = g_timer_elapsed(watch,NULL);
    g_print("%f seconds with    mempool\n",t1);
    g_print("%f seconds without mempool\n",t2);
    g_print("%f Difference, Speedup: %2.3f%%\n",t2-t1, t2/t1 * 100);
    g_print("%f seconds in total\n",t1+t2);
    g_timer_start(watch);
    SomeClass::disposeAll();
    g_timer_stop(watch);
    g_print("%f seconds to clean up\n",g_timer_elapsed(watch,NULL));
    g_timer_destroy(watch);
}
