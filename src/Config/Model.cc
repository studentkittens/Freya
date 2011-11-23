#include "Model.hh"
#include "../Log/Writer.hh"

#include <cstring>

namespace Config
{
    /*reads file from hdd*/
    Model::Model()
    {
        Init::Path path;
        Glib::ustring pfad(path.path_to_config());
        setpath((char*)pfad.c_str());
        this->load(pathtofile);
        /* loads default document to memory */
        this->loadDefaultDoc();
    }

    /* ----------------------------------------- */

    /*saves config file on exit*/
    Model::~Model()
    {
        this->save();
        xmlFreeDoc(defaultDoc);
        xmlFreeDoc(fileDoc);

    }

    /* ----------------------------------------- */

    /*returns the doc pointer of users config.xml*/
    xmlDocPtr Model::getDocPtr()
    {
        return fileDoc;
    }

    xmlDocPtr Model::getDefaultDocPtr()
    {
        return defaultDoc;
    }

    /* ----------------------------------------- */

    /*xml file reader*/
    void Model::load(char* file)
    {
        /* try loading config.xml from hdd */
        fileDoc = xmlParseFile(file);
        xmlNodePtr curNode;

        if(NULL != fileDoc)
        {
            curNode = xmlDocGetRootElement(fileDoc);
            if (NULL != curNode)
            {
                if (!(xmlStrcmp(curNode->name, (const xmlChar*) "freya")))
                {
                    Success("Config succesfully read.");
                }
                else
                {
                    Error("File does not look like a Freya config file.");
                    xmlFreeDoc(fileDoc);
                    fileDoc = NULL;
                    curNode = NULL;
                }
            }
            else
            {
                Error("Empty config file / invalid XML");
                xmlFreeDoc(fileDoc);
                fileDoc = NULL;
            }
        }
        else
        {
            Error("config.xml file not found.");
        }

    }

    /* ----------------------------------------- */

    /* loads default document */
    void Model::loadDefaultDoc()
    {
        const char* tmp = defaultconfig.c_str();
        defaultDoc =  xmlParseMemory(tmp, strlen(tmp));
    }

    /* ----------------------------------------- */

    /*save default config aka Mr fileDoc*/
    void Model::save()
    {
        save((char*)outputfile, fileDoc);
    }


    /*save alternative config*/
    void Model::save(char* altfile,xmlDocPtr doc)
    {
        xmlSaveFile(altfile,doc);
    }

    void Model::setpath(char* path)
    {
        pathtofile = path;
    }
}
