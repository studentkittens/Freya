#include <stdio.h>
#include "Utils.hh"
#include <time.h>

namespace Utils {

    Glib::ustring seconds_to_duration(unsigned long duration)
    {
        int week = duration/604800;
        duration -= (week*604800);

        int day = duration/86400;
        duration -= (day*86400);

        int hour = duration/3600;
        duration -= (hour*3600);

        int min = duration/60;
        duration -= (min*60);

        int sec = duration;

        char * durstr =  NULL;

        if (week != 0)
        {        
            durstr = g_strdup_printf("%d weeks, %d days %d hours %d minutes %d seconds\n",week,day,hour,min,sec);
        }
        else if(day != 0)
        {
            durstr = g_strdup_printf("%d days %d hours %d minutes %d seconds\n",day,hour,min,sec);
        }
        else
        {
            durstr = g_strdup_printf("%d hours %d minutes %d seconds\n",hour,min,sec);
        }
        Glib::ustring retv = durstr;
        free(durstr);

        return retv;
    }


    Glib::ustring seconds_to_timestamp(const long duration)
    {
        struct tm *timestr = NULL;
        timestr = localtime(&duration);
        
        char buffer[512]; 
        strftime (buffer,512, "%F",timestr);
    
        return Glib::ustring(buffer);
    }
}
