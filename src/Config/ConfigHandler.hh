#ifndef CONFIGHANDLER_89V106EN
#define CONFIGHANDLER_89V106EN

#include <glibmm.h>
#include <libxml/parser.h>
#include "../Singleton.hh"
#include "ConfigModel.hh"


class ConfigHandler
{
    DEF_SINGLETON( ConfigHandler )

public:
    ~ConfigHandler ();

    /*getter and setter for given node*/
    Glib::ustring get_value(Glib::ustring);
    int get_value_as_int(Glib::ustring);
    void set_value(Glib::ustring, Glib::ustring);
    void set_value_as_int(Glib::ustring,int);

private:
    /*internal traversing funcs*/
    xmlNodePtr traverse(char*, xmlNodePtr);
    xmlNodePtr _traverse(char*, char*, char*, int, xmlNodePtr);

    /*model config member for data access*/
    ConfigModel cfgmodel;

};

#define CONFIG_SET(X,Y) ConfigHandler::instance().set_value(X,Y) 
#define CONFIG_GET(X)   ConfigHandler::instance().get_value(X) 

#define CONFIG_SET_AS_INT(X,Y) ConfigHandler::instance().set_value_as_int(X,Y) 
#define CONFIG_GET_AS_INT(X)   ConfigHandler::instance().get_value_as_int(X) 

#endif /* end of include guard: CONFIGHANDLER_89V106EN */
