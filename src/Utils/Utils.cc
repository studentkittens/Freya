#include <stdio.h>
#include "Utils.hh"
#include <time.h>

namespace Utils {

    Glib::ustring seconds_to_duration(unsigned long duration)
    {
        const int BUFFER = 512;
        const int WEEK_IN_SEC = 604800;
        const int DAY_IN_SEC = 86400; 
        const int HOUR_IN_SEC = 3600;
        const int MIN_IN_SEC = 60;


        int week = duration/WEEK_IN_SEC;
        duration %= WEEK_IN_SEC;

        int day = duration/DAY_IN_SEC;
        duration %= DAY_IN_SEC;

        int hour = duration/HOUR_IN_SEC;
        duration %= HOUR_IN_SEC;

        int min = duration/MIN_IN_SEC;
        duration %= MIN_IN_SEC;

        int sec = duration;

        char durstr[BUFFER] = {0};

        if (week != 0)
        {        
            g_snprintf(durstr,BUFFER,"%d weeks %d days %d hours %d minutes %d seconds\n",week,day,hour,min,sec);
        }
        else if(day != 0)
        {

            g_snprintf(durstr,BUFFER,"%d days %d hours %d minutes %d seconds\n",day,hour,min,sec);
        }
        else
        {
            
            g_snprintf(durstr,BUFFER,"%d hours %d minutes %d seconds\n",hour,min,sec);
        }
        Glib::ustring retv = durstr;

        return retv;
    }


    Glib::ustring seconds_to_timestamp(const long duration)
    {
        int const BUFFER = 512;

        struct tm *timestr = NULL;
        timestr = localtime(&duration);
        
        char retv[BUFFER]; 
        strftime (retv,512, "%F",timestr);
    
        return Glib::ustring(retv);
    }
}
