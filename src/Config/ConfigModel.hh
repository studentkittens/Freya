#ifndef ConfigModel_ATB3SUAE
#define ConfigModel_ATB3SUAE
#define outputfile "./config.xml"
#include "./defaultcfg.inl"

#include <libxml/parser.h>

class ConfigModel
{
public:
    ConfigModel ();
    ~ConfigModel ();

    /*loader and saver funcs for xml file*/
    void load(char*);
    void save();
    /*save as different filename eg. config.xml.bak*/
    void save(char*, xmlDocPtr);

    /*xml document getter*/
    xmlDocPtr getDocPtr();

private:
    /*xml document and xml node member*/
    xmlDocPtr fileDoc;
    xmlDocPtr defaultDoc;
    xmlNodePtr curNode;
    void setpath(char*);
    char* pathtofile;
};

#endif /* end of include guard: ConfigModel_ATB3SUAE */
