#include "Request.hh"
#include "UpdateInterface.hh"
#include "../Log/Writer.hh"

#define MAX_TRIES 100

Glib::RefPtr<Glib::MainLoop> mainLoop;
int exitCtr = 0;

class Klass : public Glyr::UpdateInterface
{
public:

    void update(MPD::Client& client, mpd_idle event, MPD::NotifyData& data) {}

    /////////////////////

    void on_deliver(GlyrMemCache * c)
    {
        glyr_cache_print(c);
        glyr_free_list(c);
        if(++exitCtr == MAX_TRIES)
        {
            mainLoop->quit();
        }
    }

    /////////////////////

    bool do_stuff()
    {
        for(int i = 0; i < MAX_TRIES; i++)
        {
            if(i % 2)
            {
                Glyr::Stack::instance().request(this,"Equilibrium","Sagas",NULL,GLYR_GET_COVERART);
            }
            else
            {
                Glyr::Stack::instance().request(this,"Akrea","Lebenslinie",NULL,GLYR_GET_COVERART);
            }
        }
        return false;
    }
};

int main(int argc, char const *argv[])
{
    Klass k;
    g_thread_init(NULL);
    LogSetVerbosity(Log::LOG_INFO);
    Glyr::Stack::instance();
    mainLoop = Glib::MainLoop::create();
    Glib::signal_idle().connect(sigc::mem_fun(k,&Klass::do_stuff));
    mainLoop->run();
    Glyr::Stack::instance().destroy();
    return 0;
}
