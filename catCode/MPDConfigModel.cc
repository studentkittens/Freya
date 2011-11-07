#include "MPDConfigModel.hh"
#define outputfile "./config.xml"


/*reads file from hdd*/
MPDConfigModel::MPDConfigModel(char* pathtofile)
{
    this->load(pathtofile);
}


/*saves config file on exit*/
MPDConfigModel::~MPDConfigModel()
{
    this->save();
    xmlFreeDoc(fileDoc);
}


/*returns the doc pointer of users config.xml*/
xmlDocPtr MPDConfigModel::getDocPtr()
{
    return fileDoc;
}


/*xml file reader*/
void MPDConfigModel::load(char* file)
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
void MPDConfigModel::save()
{
    xmlSaveFile(outputfile, fileDoc);
}


/*save alternative config*/
void MPDConfigModel::save(char* altfile,xmlDocPtr doc)
{
    xmlSaveFile(altfile,doc);
}
