#ifndef MPDCONFIGMODEL_ATB3SUAE
#define MPDCONFIGMODEL_ATB3SUAE

#include <libxml/parser.h>

class MPDConfigModel
{
    public:
        MPDConfigModel (char*);
        ~MPDConfigModel ();

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
        xmlNodePtr curNode;
};

#endif /* end of include guard: MPDCONFIGMODEL_ATB3SUAE */
