/***********************************************************
* This file is part of Freya
* - A free MPD Gtk3 MPD Client -
*
* Authors: Christopher Pahl, Christoph Piechula,
*          Eduard Schneider
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
        g_free(pathtofile);

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
        save(pathtofile, fileDoc);
    }


    /*save alternative config*/
    void Model::save(char* altfile,xmlDocPtr doc)
    {
        xmlSaveFile(altfile,doc);
    }

    void Model::setpath(char* path)
    {
        pathtofile = g_strdup_printf("%s",path);
    }

}
