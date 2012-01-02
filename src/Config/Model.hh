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
#ifndef FREYA_CONFIG_MODEL_ATB3SUAE
#define FREYA_CONFIG_MODEL_ATB3SUAE

#include <libxml/parser.h>
#include "./defaultcfg.inl"
#include "../Init/Path.hh"
#define outputfile "./config.xml"

namespace Config
{
    /**
     * @brief Data needed by Config::Handler
     */
    class Model
    {
    public:
        Model ();
        ~Model ();


        /**
         * @brief loads current configuration file from hard disk as fileDoc xmlDocPtr
         *
         * @param char*,  path to config.xml file as char ptr
         */
        void load(char*);


        /**
         * @brief loads default config as defaultDoc xmlDocPtr
         */
        void loadDefaultDoc();

        /**
         * @brief saves _current_ config to hard disk (config.xml)
         */
        void save();

        /**
         * @brief alternative save function to write given xmlDoc to a given path
         *
         * @param char*, alternative path for saving config file
         * @param xmlDocPtr, alternative ptr to xmlDoc you want to save
         */
        void save(char*, xmlDocPtr);


        /**
         * @brief simple getter for xmlDocPtr
         *
         * @return xmlDocPtr to config file
         */
        xmlDocPtr getDocPtr();

        /**
         * @brief simple getter for _default_ xmlDocPtr
         *
         * @return xmlDocPtr to _default_ config
         */
        xmlDocPtr getDefaultDocPtr();

    private:
        /*xml document and xml node member*/
        xmlDocPtr fileDoc;
        xmlDocPtr defaultDoc;
        void setpath(char*);
        char* pathtofile;
    };
}

#endif /* end of include guard */
