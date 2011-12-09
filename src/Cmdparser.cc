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
#include <iostream>
#include <cstring>
#include <cstdlib>
#include <vector>

using namespace std;


// Callback for every option
typedef bool (*option_callback)(const char * optarg, void * user_ptr);

//--------------------------
//--------------------------
//--------------------------

enum OPTION_TYPE
{
    OPTION_REQUIRED,
    OPTION_OPTIONAL,
    OPTION_NOARGUMENT
};

//--------------------------

// A single commandline option
class CmdOption
{
    option_callback action;
    void * userptr;

    public:
    OPTION_TYPE type;
    string name;
    string key;
    string description;

    //--------------------------

    CmdOption(const char * name, const char key, OPTION_TYPE type, const char * description, option_callback action, void * userptr)
    {
        char keybuf[2] = {key,0};
        this->name   = "--" + string(name);
        this->key    = "-"  + string(keybuf);
        this->description = description;
        this->action = action;
        this->type   = type;
        this->userptr = userptr;
    }
    
    //--------------------------

    bool call_action(const char * optarg)
    {
        if(this->action != NULL)
        {
            return this->action(optarg,userptr);
        }
        return false;
    }

    //--------------------------
};

//--------------------------
//--------------------------
//--------------------------

class CmdArgParser
{
    vector<CmdOption> opt_vec;
    char ** m_argv;
    int m_argc;

    //----------------------
    public:
    //----------------------

    CmdArgParser(int argc, char ** argv)
    {
        m_argv = argv;
        m_argc = argc;

    }

    //----------------

    void add_option(CmdOption opt)
    {
        opt_vec.push_back(opt);
    }

    //----------------
    
    void print_help(void)
    {
        for(vector<CmdOption>::iterator it = opt_vec.begin(); it < opt_vec.end(); it++)
        {
            const char * required = NULL;
            switch(it->type)
            {
                case OPTION_NOARGUMENT: required = "NonArg"; break;
                case OPTION_OPTIONAL:   required = "OptArg"; break;
                case OPTION_REQUIRED:   required = "ReqArg"; break;
                default:                required = "unknown";
            }

            cout << it->key << " [" << required  << "] " << it->name;

            int padding = 15 - it->name.length();
            for(int i = 0; i < padding; i++)
                cout << " ";

            cout << it->description << endl;
        }
    }

    //----------------

    void parse(void)
    {
            for(int argi = 1; argi < this->m_argc; argi++)
            {
                if(m_argv[argi][0] != '-')
                    continue;

                bool option_found = false;

                for(vector<CmdOption>::iterator it = opt_vec.begin(); it < opt_vec.end(); it++)
                {
                    size_t arg_len = it->name.length();
                    if(strncmp(this->m_argv[argi],it->name.c_str(),arg_len) == 0 ||
                       strncmp(this->m_argv[argi],it->key.c_str(), 2)       == 0)
                    {
                        switch(it->type)
                        {
                            case OPTION_NOARGUMENT:
                                it->call_action(NULL);
                                break;
                            case OPTION_OPTIONAL:
                                if(argi < m_argc - 1 && strncmp(m_argv[argi+1],"--",2) != 0)
                                {
                                    it->call_action(m_argv[argi+1]);
                                }
                                else
                                {
                                    it->call_action(NULL);
                                }
                                break;
                            case OPTION_REQUIRED:
                                if(argi < m_argc - 1 && strncmp(m_argv[argi+1],"-",1) != 0)
                                {
                                    it->call_action(m_argv[argi+1]);
                                } 
                                else 
                                {
                                    cerr << "Missing argument for " << it->name << " [" << it->key << "]" << endl;
                                    cerr << "Exiting since it is marked required." << endl;
                                    exit(0);
                                }
                                break;
                            default:
                                cout << "Implementation missing" << endl;
                        }

                        option_found = true;
                        break;
                    }
                }

                if(option_found == false)
                {
                    cerr << "No such option: " << m_argv[argi] << endl;
                }
            }
    }

    // -------------- 
};

//--------------------------
//--------------------------


static bool help_action(const char * optarg, void * userptr)
{
    CmdArgParser * parser = (CmdArgParser*)userptr;
    parser->print_help();
    return optarg == NULL;
}

//--------------------------

static bool config_action(const char * optarg, void * userptr)
{
    cout << "this is the config: " << optarg << endl;
    return true;
}

//--------------------------

static bool test_action(const char * optarg, void * userptr)
{
    cout << "this is the test" << endl;
    if(optarg != NULL)
    {
        cout << optarg << endl;
    }
    return true;
}

//--------------------------

int main(int argc, char *argv[])
{
    CmdArgParser cmdParser(argc,argv);
    cmdParser.add_option(CmdOption("help",  'h', OPTION_NOARGUMENT,"Print help",help_action, &cmdParser));
    cmdParser.add_option(CmdOption("config",'c', OPTION_REQUIRED  ,"Speciy config",config_action, NULL));
    cmdParser.add_option(CmdOption("test",  't', OPTION_OPTIONAL  ,"A test option",test_action,NULL));
    cmdParser.parse();
    return EXIT_SUCCESS; 
}
