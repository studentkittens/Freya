#ifndef FREYA_CONFIG_HANDLER_89V106EN
#define FREYA_CONFIG_HANDLER_89V106EN

#include <glib.h>
#include <libxml/parser.h>

#include "Model.hh"
#include "../Singleton.hh"

namespace Config
{
    class Handler
    {
        DEF_SINGLETON( Handler )

    public:
        ~Handler ();

        /*getter and setter for given node*/
        Glib::ustring get_value(Glib::ustring);
        int get_value_as_int(Glib::ustring);
        void set_value(Glib::ustring, Glib::ustring);
        void set_value_as_int(Glib::ustring,int);
        Glib::ustring get_default_value(Glib::ustring);
        int get_default_value_as_int(Glib::ustring);
        void save_config_now();
        
    private:
        /*internal traversing funcs*/
        xmlNodePtr traverse(const char*, xmlNodePtr);
        xmlNodePtr _traverse(const char*, char*, char*, int, xmlNodePtr);

        /*model config member for data access*/
        Model cfgmodel;
        Glib::ustring _get_value(Glib::ustring, bool);
        int _get_value_as_int(Glib::ustring, bool);
    };
}

#define CONFIG_SET(x,y) Config::Handler::instance().set_value(x,y)
#define CONFIG_GET(x)   Config::Handler::instance().get_value(x)

#define CONFIG_SET_AS_INT(x,y) Config::Handler::instance().set_value_as_int(x,y)
#define CONFIG_GET_AS_INT(x)   Config::Handler::instance().get_value_as_int(x)

#define CONFIG_SAVE_NOW() Config::Handler::instance().save_config_now()

#define CONFIG_GET_DEFAULT(x) Config::Handler::instance().get_default_value(x)
#define CONFIG_GET_DEFAULT_AS_INT(x) Config::Handler::instance().get_default_value_as_int(x)

#endif /* end of include guard: Handler_89V106EN */
