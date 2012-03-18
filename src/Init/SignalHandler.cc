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
    
    //////////////////////////////////////

    static void signal_handler(int signo)
    {
        switch(signo)
        {
            case SIGINT:
                Info("Closing.");
                break;
            default:
                Critical("Freya received an unexpted signal (%s)\n"
                        "                 Please go to https://github.com/studentkittens/Freya/issues\n"
                        "                 and start to throw bad words like 'backtrace' at us.\n"
                        "                 This message was emitted from: ",
                        Glib::strsignal(signo).c_str());

                Info("Will try to save data and exit now.");
                Config::Handler::instance().save_config_now();
                exit(-42);
                break;
        }
        Gtk::Main::quit();
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
