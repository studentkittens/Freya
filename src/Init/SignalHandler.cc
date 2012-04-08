#include <gtkmm/main.h>

#ifndef G_OS_WIN32
#include <signal.h>
#endif

#include "SignalHandler.hh"
#include "../Log/Writer.hh"
#include "../Config/Handler.hh"

//////////////////////////////////////

namespace Init
{

#ifndef G_OS_WIN32
static struct sigaction sa_struct;
static int killCtr = 0;

//////////////////////////////////////

static void signal_handler(int signo)
{
    const char * sigstr = g_strsignal(signo);
    switch(signo)
    {
    case SIGINT:
    {
        Info("Closing.");
        if(killCtr > 1)
        {
            Config::Handler::instance().save_config_now();
            Error("Pressed Ctrl-C twice or more");
            exit(-23);
        }
        killCtr++;
        Gtk::Main::quit();
        break;
    }
    case SIGABRT:
    case SIGSEGV:
    case SIGFPE:
    {
        Critical("Freya received an unexpted signal (%s)\n"
                 "                 Please go to https://github.com/studentkittens/Freya/issues\n"
                 "                 and start to throw bad words like 'backtrace' at us.\n"
                 "                 This message was emitted from: ",
                 sigstr);
        Config::Handler::instance().save_config_now();
        exit(-42);
        break;
    }
    default:
    {
        Warning("Received unknown signal: %s",sigstr);
    }
    }
}
#endif

//////////////////////////////////////

SignalHandler::SignalHandler()
{
#ifndef G_OS_WIN32
    sa_struct.sa_handler = signal_handler;
    sigemptyset(&sa_struct.sa_mask);
    sa_struct.sa_flags = 0;
    /* Register all relevant signals */
    sigaction(SIGSEGV,&sa_struct,NULL);
    sigaction(SIGFPE,&sa_struct,NULL);
    sigaction(SIGABRT,&sa_struct,NULL);
    sigaction(SIGINT, &sa_struct,NULL);
#endif
}
}
