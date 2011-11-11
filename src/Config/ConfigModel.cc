#include "ConfigModel.hh"
#include <string.h>

/*reads file from hdd*/
ConfigModel::ConfigModel()
{
    setpath((char*)outputfile);
    this->load(pathtofile);
}

/* ----------------------------------------- */

/*saves config file on exit*/
ConfigModel::~ConfigModel()
{
    this->save();
    xmlFreeDoc(fileDoc);
}

/* ----------------------------------------- */

/*returns the doc pointer of users config.xml*/
xmlDocPtr ConfigModel::getDocPtr()
{
    return fileDoc;
    //return defaultDoc;
}

/* ----------------------------------------- */

/*xml file reader*/
void ConfigModel::load(char* file)
{
    fileDoc = xmlParseFile(file);

    if(NULL != fileDoc)
    {
        curNode = xmlDocGetRootElement(fileDoc);
        if (NULL != curNode)
        {
            if (!(xmlStrcmp(curNode->name, (const xmlChar*) "freya")))
            {
                printf("INFO: config successfully read.\n");
            }
            else
            {
                printf("ERROR: wrong config file.\n");
                curNode = NULL;
            }
        }
        else
        {
            printf("ERROR: empty config file.\n");
        }
    }
    else
    {
        printf("ERROR: config.xml file not found.\n");
        fileDoc = NULL;
    }

    /* load default config to ram */
    //const char* tmp = defaultconfig.c_str();
    //defaultDoc =  xmlParseMemory(tmp, strlen(tmp));
}

/* ----------------------------------------- */

/*save default config aka Mr fileDoc*/
void ConfigModel::save()
{
    save((char*)outputfile, fileDoc);
}

/* ----------------------------------------- */

/*save alternative config*/
void ConfigModel::save(char* altfile,xmlDocPtr doc)
{
    xmlSaveFile(altfile,doc);
}

void ConfigModel::setpath(char* path)
{
    pathtofile = path;
}
