#ifndef __LOGHANDLER
#define __LOGHANDLER

#include <stdio.h>
#include "Singleton.hh"
#define LOGFILE_PATH "logfile.txt"

/* Not supposed to used diretly, use the macros below */
#define _MSG(level, msg, ...) LogHandler::instance().message(__FILE__, __LINE__, level, msg,  ##__VA_ARGS__)

/* The actual macros */
#define Warning(msg, ...)  _MSG(LOG_WARN, msg, ##__VA_ARGS__)
#define Info(msg, ...)     _MSG(LOG_INFO, msg, ##__VA_ARGS__)
#define Fatal(msg, ...)    _MSG(LOG_FATAL_ERROR, msg, ##__VA_ARGS__)
#define Error(msg, ...)    _MSG(LOG_ERROR, msg, ##__VA_ARGS__)
#define Debug(msg, ...)    _MSG(LOG_DEBUG, msg, ##__VA_ARGS__)
#define Success(msg, ...)  _MSG(LOG_OK, msg, ##__VA_ARGS__)


/**
everitylevel
         * @param msg Actual message
         * @param ... a va_list to allow printf style logging
         */

 */
enum LOGLEVEL {
    LOG_OK,
    LOG_ERROR,
    LOG_FATAL_ERROR,
    LOG_INFO,
    LOG_WARN,
    LOG_DEBUG
};

class LogHandler 
{
    /* Make this class a singleton,
     * this implicitely defines a ctor,
     * Just the dtor is defined expl. below.
     */
    DEF_SINGLETON(LogHandler);
    
    public:
        ~LogHandler();
        /**
         * @brief Actual instance method called. Do not use directly! 
         *
         * @param file Passed by the macro.
         * @param line Passed by the macro.
         * @param level Severitylevel
         * @param msg Actual message
         * @param ... a va_list to allow printf style logging
         */
        void message(const char *file, int line, LOGLEVEL level, const char *msg, ...); 		
        /**
         * @brief Clear the logfile (but keep it open)
         */
        void clear(void);

    private:
        FILE * m_Logfile;                                                              	
        const char * convert_enum_to_str(LOGLEVEL level);                                       
        const char * convert_enum_to_col(LOGLEVEL level);                                       
        void get_current_time(char buffer[]);									
};

#endif
