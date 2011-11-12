#include "Model.hh"
#include "../Log/Writer.hh"

#include <cstring>

namespace Config
{
    /*reads file from hdd*/
    Model::Model()
    {
        setpath((char*)outputfile);
        this->load(pathtofile);
    }

    /* ----------------------------------------- */

    /*saves config file on exit*/
    Model::~Model()
    {
        this->save();
        xmlFreeDoc(fileDoc);
    }

    /* ----------------------------------------- */

    /*returns the doc pointer of users config.xml*/
    xmlDocPtr Model::getDocPtr()
    {
        return fileDoc;
        //return defaultDoc;
    }

    /* ----------------------------------------- */

    /*xml file reader*/
    void Model::load(char* file)
    {
        fileDoc = xmlParseFile(file);

        if(NULL != fileDoc)
        {
            curNode = xmlDocGetRootElement(fileDoc);
            if (NULL != curNode)
            {
                if (!(xmlStrcmp(curNode->name, (const xmlChar*) "freya")))
                {
                    Info("Config succesfully read.");
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
            printf("ERROR: config.xml file not found.\n");
        }

        /* load default config to ram */
        //const char* tmp = defaultconfig.c_str();
        //defaultDoc =  xmlParseMemory(tmp, strlen(tmp));
    }

    /* ----------------------------------------- */

    /*save default config aka Mr fileDoc*/
    void Model::save()
    {
        save((char*)outputfile, fileDoc);
    }

    /* ----------------------------------------- */

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
