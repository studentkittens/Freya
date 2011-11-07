<<<<<<< HEAD:catCode/ConfigHandler.hh
#ifndef CONFIGHANDLER_89V106EN

#define CONFIGHANDLER_89V106EN

#include <gtkmm.h>
=======
#ifndef CONFIGHANDLER_6JC28HEQ
#define CONFIGHANDLER_6JC28HEQ

#include <glibmm.h>
>>>>>>> 1d6cd4ff339236199cfcc22e4b577a7e27fea1a6:src/Config/ConfigHandler.hh
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

#endif /* end of include guard: CONFIGHANDLER_89V106EN */





<<<<<<< HEAD:catCode/ConfigHandler.hh
=======
#endif /* end of include guard: ConfigHandler_6JC28HEQ */
>>>>>>> 1d6cd4ff339236199cfcc22e4b577a7e27fea1a6:src/Config/ConfigHandler.hh











