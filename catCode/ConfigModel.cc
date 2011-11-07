#include "ConfigModel.hh"
#define outputfile "./config.xml"


/*reads file from hdd*/
ConfigModel::ConfigModel(char* pathtofile)
{
    this->load(pathtofile);
}


/*saves config file on exit*/
ConfigModel::~ConfigModel()
{
    this->save();
    xmlFreeDoc(fileDoc);
}


/*returns the doc pointer of users config.xml*/
xmlDocPtr ConfigModel::getDocPtr()
{
    return fileDoc;
}


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
}



/*save default config aka Mr fileDoc*/
void ConfigModel::save()
{
    save((char*)outputfile, fileDoc);
}


/*save alternative config*/
void ConfigModel::save(char* altfile,xmlDocPtr doc)
{
    xmlSaveFile(altfile,doc);
}
