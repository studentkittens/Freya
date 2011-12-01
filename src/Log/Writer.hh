#ifndef FREYA_LOG_WRITER_GUARD
#define FREYA_LOG_WRITER_GUARD

#include <glibmm.h>
#include <stdio.h>
#include "../Singleton.hh"

/* Not supposed to used directly, use the macros below */
#define _MSG(level, msg, ...) Log::Writer::instance().message(__FILE__, __LINE__, level, msg,  ##__VA_ARGS__)

/* The actual macros */
#define Warning(msg, ...)  _MSG(Log::LOG_WARN, msg, ##__VA_ARGS__)
#define Info(msg, ...)     _MSG(Log::LOG_INFO, msg, ##__VA_ARGS__)
#define Fatal(msg, ...)    _MSG(Log::LOG_FATAL_ERROR, msg, ##__VA_ARGS__)
#define Error(msg, ...)    _MSG(Log::LOG_ERROR, msg, ##__VA_ARGS__)
#define Debug(msg, ...)    _MSG(Log::LOG_DEBUG, msg, ##__VA_ARGS__)
#define Success(msg, ...)  _MSG(Log::LOG_OK, msg, ##__VA_ARGS__)

namespace Log
{
    /**
     * @brief Log severity, influencing the color. 
     */
    enum LOGLEVEL {
        LOG_OK,
        LOG_ERROR,
        LOG_FATAL_ERROR,
        LOG_INFO,
        LOG_WARN,
        LOG_DEBUG
    };

    class Writer 
    {
        friend TestLog;

        /* Make this class a singleton,
         * this implicitely defines a ctor,
         * Just the dtor is defined expl. below.
         */
        DEF_SINGLETON(Writer);

        public:

        ~Writer();
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

        Glib::ustring m_Logpath;
        FILE * m_Logfile;                                                              	

        const char * convert_enum_to_str(LOGLEVEL level);                                       
        const char * convert_enum_to_col(LOGLEVEL level);                                       
        void get_current_time(char buffer[]);									
    };
}

#endif
