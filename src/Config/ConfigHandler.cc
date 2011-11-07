#include "ConfigHandler.hh"
#include <cstring>
#define URL_DELIMITER '.'

/*ctor creates model which encapsulates the config*/
MPDConfigHandler::MPDConfigHandler(char* pathtofile):cfgmodel(pathtofile)
{}

/* ----------------------------------------- */

MPDConfigHandler::~MPDConfigHandler()
{}


/* ----------------------------------------- */

/*returns value of a given node if avaiable*/
Glib::ustring& MPDConfigHandler::get_value(Glib::ustring url)
{
    xmlDocPtr doc = cfgmodel.getDocPtr();
    xmlNodePtr cur = NULL;

    if (doc != NULL)
    {
        cur = xmlDocGetRootElement(doc);
        cur=cur->xmlChildrenNode;
        cur = (this->traverse((char*)url.c_str(),cur));
    }

    Glib::ustring* copy = NULL;
    xmlChar* key = NULL;

    if (cur!=NULL)
    {
        key = xmlNodeListGetString(doc, cur->xmlChildrenNode, true);
        copy    = new Glib::ustring((char*)key);
        xmlFree(key);
    }
    else
    {
        copy    = new Glib::ustring((char*)"");
    }
    return *(copy);
}

/* ----------------------------------------- */

/*sets given value if node avaiable*/
void MPDConfigHandler::set_value(Glib::ustring url,Glib::ustring value)
{
    xmlDocPtr doc = cfgmodel.getDocPtr();
    if (NULL != doc)
    {
        /*prepare for traversing*/
        xmlNodePtr cur = xmlDocGetRootElement(doc);
        cur=cur->xmlChildrenNode;
        cur = (this->traverse((char*)url.c_str(),cur));

        /*insert into valid node*/
        if (cur != NULL)
            xmlNodeSetContent(cur, (xmlChar*)value.c_str());
    }
}

/* ----------------------------------------- */

/*subroutine for preparing traversation*/
xmlNodePtr MPDConfigHandler::traverse(char * url, xmlNodePtr cur)
{
    if(NULL != url)
    {
        char * p1 = strchrnul(url,URL_DELIMITER);
        char * p2 = strchrnul((p1+1),URL_DELIMITER);
        int len = ABS(url-p1);

        return this->_traverse(url,p1,p2,len,cur);
    }
    else
    {
        printf("nothing to do");
        return NULL;
    }

}

/* ----------------------------------------- */

/*traverse and return node pointer or nothing*/
xmlNodePtr MPDConfigHandler::_traverse(char* url, char* p1, char* p2, int len, xmlNodePtr cur)
{
    xmlNodePtr result = NULL;

    if (NULL != cur)
    {
        while (NULL != cur)
        {
            /*check if len an string matches*/
            if (len == (int)strlen((char*)cur->name) && (!xmlStrncmp(cur->name, (const xmlChar *)url, len)))
            {
                /*if at last '.' position, print result*/
                if(url == (p2+1))
                {
                    result = cur;
                }
                /*set url ptr to next dot*/
                else if (url == (p1+1))
                {
                    url = (p2+1);
                    len = strlen(url);
                    cur=cur->xmlChildrenNode;       /*jump to next level*/
                    this->_traverse(url,p1,p2,len,cur);
                }
                else
                {
                    url = (p1+1);
                    len = ABS(p2-url);
                    cur=cur->xmlChildrenNode;       /*jump to next level*/
                    this->_traverse(url,p1,p2,len,cur);
                }

            }
            cur = cur->next;
        }
        return result;
    }
    else
    {
        printf("error: value not found\n");
        return result;
    }
}
