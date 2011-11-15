#ifndef FREYA_CONFIG_MODEL_ATB3SUAE
#define FREYA_CONFIG_MODEL_ATB3SUAE

#include <libxml/parser.h>
#include "./defaultcfg.inl"
#include "../Init/Initpath.hh"
#define outputfile "./config.xml"

namespace Config
{
class Model
{
public:
    Model ();
    ~Model ();

    /*loader and saver funcs for xml file*/
    void load(char*);
    void loadDefaultDoc();
    void save();
    /*save as different filename eg. config.xml.bak*/
    void save(char*, xmlDocPtr);
    void write_default();
    void write_default(char*);

    /*xml document getter*/
    xmlDocPtr getDocPtr();
    xmlDocPtr getDefaultDocPtr();

private:
    /*xml document and xml node member*/
    xmlDocPtr fileDoc;
    xmlDocPtr defaultDoc;
    void setpath(char*);
    char* pathtofile;
};
}

#endif /* end of include guard */
