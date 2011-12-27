 /***********************************************************
* This file is part of Freya 
* - A free MPD Gtk3 MPD Client -
* 
* Authors: Christopher Pahl, Christoph Piechula,
*          Eduard Schneider, Marc Tigges
*
* Copyright (C) [2011-2012]
* Hosted at: https://github.com/studentkittens/Freya
*
*              __..--''``---....___   _..._    __
*    /// //_.-'    .-/";  `        ``<._  ``.''_ `. / // /
*   ///_.-' _..--.'_                        `( ) ) // //
*   / (_..-' // (< _     ;_..__               ; `' / ///
*    / // // //  `-._,_)' // / ``--...____..-' /// / //  
*  Ascii-Art by Felix Lee <flee@cse.psu.edu>
*
* Freya is free software: you can redistribute it and/or modify
* it under the terms of the GNU General Public License as published by
* the Free Software Foundation, either version 3 of the License, or
* (at your option) any later version.
*
* Freya is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
* GNU General Public License for more details.
*
* You should have received a copy of the GNU General Public License
* along with Freya. If not, see <http://www.gnu.org/licenses/>.
**************************************************************/
#include "Handler.hh"
#include "../Log/Writer.hh"

#include <cstring>
#include <glib.h>

#define URL_DELIMITER '.'

namespace Config
{
    /*ctor creates model which encapsulates the config*/
    Handler::Handler()
    {}

    /* ----------------------------------------- */

    Handler::~Handler()
    {}

    /* ----------------------------------------- */

    /*returns value of a given node if avaiable*/
    Glib::ustring Handler::get_value(Glib::ustring url)
    {
        return _get_value(url,false);
    }

    /* ----------------------------------------- */

    Glib::ustring Handler::_get_value(Glib::ustring url, bool getdefault)
    {
        xmlDocPtr doc;
        if (getdefault)
        {
            doc = cfgmodel.getDefaultDocPtr();
        }
        else
        {
            doc = cfgmodel.getDocPtr();
        }

        xmlNodePtr cur = NULL;
        xmlChar* key = NULL;

        if (doc != NULL)
        {
            cur = xmlDocGetRootElement(doc);
            cur=cur->xmlChildrenNode;
            cur = (this->traverse(url.c_str(),cur));
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
            /* trying to get default value for given url */
            if(!getdefault)
            {
                Warning("Value not found, fallback to default value if avaiable.");
                return _get_value(url,true);
            }
            else
            {
                return Glib::ustring("");
            }
        }
    }



    /* ----------------------------------------- */
    int Handler::get_value_as_int(Glib::ustring url)
    {
        return _get_value_as_int(url,false);
    }
    
    int Handler::_get_value_as_int(Glib::ustring url, bool getdefault)
    {
        char * tmp = NULL;
        int result;

        if (getdefault)
        {
            result = g_ascii_strtoll(get_default_value(url).c_str(),&tmp,10);
        }
        else
        {
            result = g_ascii_strtoll(get_value(url).c_str(),&tmp,10);
        }

        if ((NULL == tmp) && (0 == result))
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
    void Handler::set_value(Glib::ustring url,Glib::ustring value)
    {
        xmlDocPtr doc = cfgmodel.getDocPtr();
        if (NULL != doc)
        {
            /*prepare for traversing*/
            xmlNodePtr cur = xmlDocGetRootElement(doc);
            cur=cur->xmlChildrenNode;
            cur = (this->traverse(url.c_str(),cur));

            /*insert into valid node*/
            if (cur != NULL)
                xmlNodeSetContent(cur, (xmlChar*)value.c_str());
        }
        else
        {
            Warning("DocPtr is NULL, cannot write given value %s to %s.", value.c_str(), url.c_str());
        }
    }


    void Handler::set_value_as_int(Glib::ustring url,int value)
    {
        char* copy = g_strdup_printf("%d",value);
        set_value(url, copy);
        g_free(copy);
    }


    /* ----------------------------------------- */

    /*subroutine for preparing traversation*/
    xmlNodePtr Handler::traverse(const char * url, xmlNodePtr cur)
    {
        if(NULL != url)
        {
            char * marker_prev = strchrnul((char*)url,URL_DELIMITER);
            char * marker_next = strchrnul((marker_prev+1),URL_DELIMITER);
            int len = ABS(url-marker_prev);

            xmlNodePtr node = this->_traverse(url,marker_prev,marker_next,len,cur);
            if(node == NULL)
                Warning("%s does not exist in config",url);

            return node;
        }
        else
        {
            Warning("URL should not be NULL");
            return NULL;
        }
    }

    /* ----------------------------------------- */

    /*traverse and return node pointer or nothing*/
    xmlNodePtr Handler::_traverse(const char* url, char* marker_prev, char* marker_next, int len, xmlNodePtr cur)
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
                    if(url == (marker_next+1))
                    {
                        result = cur;
                    }
                    else
                    {
                        /*set url ptr to next dot*/
                        if (url == (marker_prev+1))
                        {
                            url = (marker_next+1);
                            len = strlen(url);
                        }
                        else
                        {
                            url = (marker_prev+1);
                            len = ABS(marker_next-url);
                        }
                        /*jump to next level*/
                        cur=cur->xmlChildrenNode;
                        this->_traverse(url,marker_prev,marker_next,len,cur);
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

    void Handler::save_config_now()
    {
        cfgmodel.save();
        Info("Trying to save config now.");
    }

    Glib::ustring Handler::get_default_value(Glib::ustring url)
    {
        return _get_value(url,true);
    }

    int Handler::get_default_value_as_int(Glib::ustring url)
    {
        return _get_value_as_int(url,true);
    }


    /* ----------------------------------------- */

    void Handler::add_server_output(Glib::ustring hostname, Glib::ustring outName, bool active)
    {
        xmlDocPtr doc;
        xmlNodePtr cur;
        xmlNodePtr tmp;
        doc = cfgmodel.getDocPtr();

        if (doc == NULL)
        {
            return;
        }

        cur = xmlDocGetRootElement(doc);

        if (cur == NULL)
        {
            return;
        }


        cur = this->traverse("freya.settings.server",cur);

        tmp = cur->xmlChildrenNode;
        while (tmp != NULL)
        {
            if ((!xmlStrcmp(tmp->name, (xmlChar*)"hostname")))
            {
                xmlChar *key = xmlGetProp(tmp, (xmlChar*)"h");
                if((!xmlStrcmp(key, (xmlChar*)hostname.c_str())))
                {
                    break;
                }
                xmlFree(key);
            }
            tmp = tmp->next;
        }

        if (tmp == NULL)
        {
            tmp = xmlNewChild(cur,NULL,(xmlChar*)"hostname",NULL);
            xmlNewProp(tmp,(xmlChar*)"h",(xmlChar*)hostname.c_str());
        }
        cur=tmp;

        tmp = tmp->xmlChildrenNode;
        while (tmp != NULL)
        {
            {
                xmlChar *key = xmlGetProp(tmp, (xmlChar*)"n");
                if((!xmlStrcmp(key, (xmlChar*)outName.c_str())))
                {
                    break;
                }
                xmlFree(key);
            }
            tmp = tmp->next;
        }

        if (tmp != NULL)
        {
            xmlNodeSetContent(tmp, (xmlChar*)(active?"1":"0"));
        }
        else
        {
            tmp = xmlNewChild(cur,NULL,(xmlChar*)"output",(xmlChar*)(active?"1":"0"));
            xmlNewProp(tmp,(xmlChar*)"n",(xmlChar*)outName.c_str());
        }
    }

    int Handler::get_server_output(Glib::ustring hostname, Glib::ustring outName)
    {
        xmlDocPtr doc;
        xmlNodePtr cur;
        xmlNodePtr tmp;
        doc = cfgmodel.getDocPtr();

        if (doc == NULL)
        {

            return 1;
        }

        cur = xmlDocGetRootElement(doc);

        if (cur == NULL)
        {
            return 1;
        }


        cur = this->traverse("freya.settings.server",cur);

        tmp = cur->xmlChildrenNode;
        while (tmp != NULL)
        {
            if ((!xmlStrcmp(tmp->name, (xmlChar*)"hostname")))
            {
                xmlChar *key = xmlGetProp(tmp, (xmlChar*)"h");
                if((!xmlStrcmp(key, (xmlChar*)hostname.c_str())))
                {
                    break;
                }
                xmlFree(key);
            }
            tmp = tmp->next;
        }

        if (tmp == NULL)
        {
            return 1;
        }
        cur=tmp;

        tmp = tmp->xmlChildrenNode;
        while (tmp != NULL)
        {
            {
                xmlChar *key = xmlGetProp(tmp, (xmlChar*)"n");
                if((!xmlStrcmp(key, (xmlChar*)outName.c_str())))
                {
                    break;
                }
                xmlFree(key);
            }
            tmp = tmp->next;
        }


        if (tmp == NULL)
        {
            return 1;
        }
        xmlChar* res =xmlNodeListGetString(doc,tmp->xmlChildrenNode,1);
        int ret = xmlStrcmp(res, (xmlChar*)"0");
        xmlFree(res);
        return ret;
    }
}
