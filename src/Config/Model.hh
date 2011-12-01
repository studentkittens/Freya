#ifndef FREYA_CONFIG_MODEL_ATB3SUAE
#define FREYA_CONFIG_MODEL_ATB3SUAE

#include <libxml/parser.h>
#include "./defaultcfg.inl"
#include "../Init/Path.hh"
#define outputfile "./config.xml"

namespace Config
{
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
