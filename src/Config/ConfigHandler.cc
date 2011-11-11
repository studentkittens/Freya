#include "ConfigHandler.hh"
#include "../LogHandler/LogHandler.hh"
#include <cstring>
#include <glib.h>
#define URL_DELIMITER '.'

/*ctor creates model which encapsulates the config*/
ConfigHandler::ConfigHandler()
{}

/* ----------------------------------------- */

ConfigHandler::~ConfigHandler()
{}

/* ----------------------------------------- */

/*returns value of a given node if avaiable*/
Glib::ustring ConfigHandler::get_value(Glib::ustring url)
{
    xmlDocPtr doc = cfgmodel.getDocPtr();
    xmlNodePtr cur = NULL;
    xmlChar* key = NULL;

    if (doc != NULL)
    {
        cur = xmlDocGetRootElement(doc);
        cur=cur->xmlChildrenNode;
        cur = (this->traverse((char*)url.c_str(),cur));
    }

    if (cur!=NULL)
    {
        key = xmlNodeListGetString(doc, cur->xmlChildrenNode, true);
        Glib::ustring retv = Glib::ustring((char*)key);
        xmlFree(key);
        return retv;
    }
    else
    {
        return Glib::ustring("");
    }
}


int ConfigHandler::get_value_as_int(Glib::ustring url)
{
    char * tmp = NULL;
    int result = g_ascii_strtoll(get_value(url).c_str(),&tmp,10);

    if (NULL != tmp && 0 == result)
    {
        return -1;
    }
    else
    {
        return result;
    }
}

/* ----------------------------------------- */

/*sets given value if node avaiable*/
void ConfigHandler::set_value(Glib::ustring url,Glib::ustring value)
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


void ConfigHandler::set_value_as_int(Glib::ustring url,int value)
{
    char* copy = (char*)g_strdup_printf("%d",value);
    set_value(url, copy);       
    g_free(copy);
}


/* ----------------------------------------- */

/*subroutine for preparing traversation*/
xmlNodePtr ConfigHandler::traverse(char * url, xmlNodePtr cur)
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
        Warning("URL should not be NULL");
        return NULL;
    }
}

/* ----------------------------------------- */

/*traverse and return node pointer or nothing*/
xmlNodePtr ConfigHandler::_traverse(char* url, char* p1, char* p2, int len, xmlNodePtr cur)
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
        Warning("URL '%s' does not yield a value.",url);
        return result;
    }
}
