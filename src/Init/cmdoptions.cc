#include <glib.h>
#include <gtk/gtk.h>
#include <stdlib.h>
#include <string.h>

#include "../Log/Writer.hh"
#include "../Config/Handler.hh"
#include "../Init/Path.hh"

#include "../../config.h"

namespace Init
{

static void do_print_version(void)
{
    g_print("Version %d.%d.%d (%s) of [%s] compiled at [%s]\n",
            FREYA_VERSION_MAJOR_INT,
            FREYA_VERSION_MINOR_INT,
            FREYA_VERSION_MICRO_INT,
            FREYA_VERSION_NAME,
            __DATE__,
            __TIME__
           );
}

static void do_print_bug_report(void)
{
    g_print("Please include this information when reporting a crash,       \n"
            "or other weird behaviour which is clearly not a feature.      \n"
            "\nThanks a lot in advance. (especially when using Pastebin :))\n"
            "\nProgram version:\n");
            
    do_print_version(); 

    g_print("\nWill print configuration and a portion of the log.\n");

    Init::Path get_cfg_dir;
    Glib::ustring command =
        "cat " + get_cfg_dir.path_to_config() + ";"
        "echo '\n\n/////////////////\n\n';" 
        "cat " + get_cfg_dir.path_to_log() + " | tail -n 70;"
        ;

    system(command.c_str());
}

/*
 * A simple C-Style commandline parser,
 * using GOptionContext (the Glibmm API is.. tedious)
 */
static gboolean print_bug_report  = FALSE;
static gboolean print_version     = FALSE;
static gboolean inc_verbosity     = FALSE;
static const gchar **override_opt = NULL;
static const gchar * hostname_opt = NULL;
static gint port_opt              = 0;

static GOptionEntry entries[] =
{
    { "bug-report", 0, 0, G_OPTION_ARG_NONE,        &print_bug_report, "Print a report suitable for the bugtracker", 0 },
    { "version",  'V', 0, G_OPTION_ARG_NONE,        &print_version,    "Print version and exit",0 },
    { "verbose",  'v', 0, G_OPTION_ARG_NONE,        &inc_verbosity,    "Increase verbosity to Debug output",0 },
    { "override", 'o', 0, G_OPTION_ARG_STRING_ARRAY,&override_opt,     "Override any option explicitly (there may be shortcuts below!)","freya.some.opt=value" },
    { "host",     'H', 0, G_OPTION_ARG_STRING,      &hostname_opt,     "Override Hostname","H" },
    { "port",     'p', 0, G_OPTION_ARG_INT,         &port_opt,         "Override Portname","P" },
    { 0,0,0,G_OPTION_ARG_NONE,0,0,0 }
};

void parse_and_handle_arguments(int argc, char *argv[])
{
    GError * error = NULL;
    GOptionContext * context;
    context = g_option_context_new("- Freya Features accesible from the commandline");
    g_option_context_add_main_entries(context, entries, "Freya");
    g_option_context_add_group(context, gtk_get_option_group(FALSE));
    if(!g_option_context_parse(context, &argc, &argv, &error))
    {
        g_print("option parsing failed: %s\n", error->message);
        g_error_free(error);
        exit(1);
    }
    else
    {
        if(print_bug_report)
        {
            do_print_bug_report();
            exit(0);
        }
        if(print_version)
        {
            do_print_version();
            // Ealry calls to exit is okay here,
            // since nothing was reall written to config/log
            exit(0);
        }

        if(inc_verbosity)
        {
            LogSetVerbosity(Log::LOG_DEBUG);
        }
        else
        {
            LogSetVerbosity(Log::LOG_INFO);
        }

        while(override_opt && *override_opt)
        {
            gchar * key = g_strdup(*override_opt);
            gchar * val = strchr(key,'=');
            if(val != NULL)
            {
                /* Split string cheaply */
                *val++ = 0;
                Debug("Overriding setting: %s with %s",key,val);
                CONFIG_SET(key,val);
            }
            else
            {
                Error("Expected Input for -o in this form: config.file.uri=value");
                Error("Example: -o settings.connection.port=6600 is the same as -p 6600");
            }
            override_opt++;
        }
        if(override_opt)
        {
            CONFIG_SAVE_NOW();
        }
        if(hostname_opt)
        {
            CONFIG_SET("settings.connection.host",hostname_opt);
        }
        if(port_opt)
        {
            CONFIG_SET_AS_INT("settings.connection.port",port_opt);
        }
    }
}
} // namespace Init
