#include "LogHandler.hh"

#include <string.h>
#include <stdlib.h>
#include <time.h>

#include <glib.h> /* g_strdup_printf() */
/* Somehow needed to prevent some compiler warning.. */
#include <glib/gprintf.h>

#define TIME_BUF_SIZE 128

/* Those work sadly only on Unix */
#define COL_RED "\x1b[31;01m"
#define COL_YEL "\x1b[33;01m"
#define COL_GRE "\x1b[32;01m"
#define COL_BLU "\x1b[34;01m"
#define COL_NCO "\x1b[0m"

/*-----------------------------------------------*/

// constructor
LogHandler::LogHandler()
{
    const char * logName = LOGFILE_PATH; 

    try 
    {
        m_Logfile = fopen(logName, "a");
        if (m_Logfile == NULL)
        {
            throw "Datei konnte nicht geoeffnet werden!";
        }
        fprintf(m_Logfile,"#####################################\n");
    } 
    catch (const char * ErrorString)
    {
        g_error("Cannot open logfile: %s",ErrorString);
        g_error("Tried to write it at: %s",logName);
    }
}

/*-----------------------------------------------*/

// destructor
LogHandler::~LogHandler()
{
    if(this->m_Logfile != NULL) {
        fclose(m_Logfile);
    }
}

/*-----------------------------------------------*/

// message method to print a message into the logfile with LOGLEVEL
void LogHandler::message(const char * File, int Line, LOGLEVEL level, const char * fmt, ...) 
{
    if(this->m_Logfile != NULL)
    {
        gchar * tmp_buf = NULL;

        va_list params;
        va_start(params,fmt);
        g_vasprintf(&tmp_buf,fmt,params);
        va_end(params);

        char buffer[TIME_BUF_SIZE] = {0};
        get_current_time(buffer);

        /* Formatting */
        gchar * format = g_strdup_printf("[%s - %s] %s (at %s:%d)\n", convert_enum_to_str(level), buffer, tmp_buf, File, Line);
        gsize fmt_len = strlen(format);

        /* Write it to all buffers */
        fwrite(format,1,fmt_len,m_Logfile);
        fwrite(format,1,fmt_len,stderr);
        fflush(m_Logfile);

        /* Format is dyn. allocated - free */
        g_free(format);
        g_free(tmp_buf);
    }
}

/*-----------------------------------------------*/

const char* LogHandler::convert_enum_to_str(LOGLEVEL level) 
{
    switch(level) {
        case LOG_OK: 
            return COL_GRE"SUC"COL_NCO;
        case LOG_ERROR:
            return COL_RED"ERR"COL_NCO;
        case LOG_FATAL_ERROR:
            return COL_RED"FTL"COL_NCO;
        case LOG_INFO:
            return COL_NCO"INF"COL_NCO;
        case LOG_WARN:
            return COL_YEL"WRN"COL_NCO;
        case LOG_DEBUG: 
            return COL_BLU"DBG"COL_NCO;
        default:
            return COL_NCO"INF"COL_NCO;
    }
}

/*-----------------------------------------------*/

void LogHandler::clear(void)
{
    if(this->m_Logfile != NULL)
    {
        fclose(m_Logfile);
        this->m_Logfile = fopen(LOGFILE_PATH,"w");
    }
}

/*-----------------------------------------------*/

void LogHandler::get_current_time(char buffer[]) 
{
    struct tm * timeinfo = NULL;
    time_t rawtime = time(NULL);
    timeinfo = localtime(&rawtime);
    strftime(buffer, TIME_BUF_SIZE, "%H:%M:%S", timeinfo);
}
