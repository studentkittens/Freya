#ifndef CONFIGHANDLER_6JC28HEQ
#define CONFIGHANDLER_6JC28HEQ

#include <glibmm.h>
#include <libxml/parser.h>
#include "ConfigModel.hh"

class ConfigHandler
{
public:
    ConfigHandler (char*);
    ~ConfigHandler ();

    /*getter and setter for given node*/
    Glib::ustring& get_value(Glib::ustring);
    void set_value(Glib::ustring, Glib::ustring);

private:
    /*internal traversing funcs*/
    xmlNodePtr traverse(char*, xmlNodePtr);
    xmlNodePtr _traverse(char*, char*, char*, int, xmlNodePtr);

    /*model config member for data access*/
    ConfigModel cfgmodel;
};


#endif /* end of include guard: ConfigHandler_6JC28HEQ */











