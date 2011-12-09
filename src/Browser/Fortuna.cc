#include "Fortuna.hh"
#include "../Utils/Utils.hh"
#include <algorithm>

#define FORTUNE_BUF_SIZE 1024
#define FORTUNE_COMMAND  "fortune -s -n 500"

namespace Browser
{
    Fortuna::Fortuna(Glib::RefPtr<Gtk::Builder>& builder) :
        AbstractBrowser("Fortuna",false,true,Gtk::Stock::DIALOG_QUESTION)
    {
        BUILDER_ADD(builder,"ui/Startscreen.glade");
        BUILDER_GET(builder,"fortune_scrolledwindow",mp_FortuneScroll);
        BUILDER_GET(builder,"fortune_label",mp_FortuneLabel);
        BUILDER_GET(builder,"fortune_refresh",mp_FortuneRefresh);
        
        mp_FortuneRefresh->signal_clicked().connect(
                sigc::mem_fun(*this,&Fortuna::on_refresh_fortune));

        on_refresh_fortune();        
    }

    /*-----------------------*/

    Gtk::Widget * Fortuna::get_container(void)
    {
        return mp_FortuneScroll;
    }
    
    /*-----------------------*/
    
    void Fortuna::on_refresh_fortune(void)
    {
        Glib::ustring fortune = get_fortune();
        if(!fortune.empty())
        {
            mp_FortuneLabel->set_markup(fortune);
        }
    }

    //----------------------------

    Glib::ustring Fortuna::get_fortune(void)
    {
        Glib::ustring retv = "";

        /* Open a pipe to the fortune command and read from it,
         * if it isn't installed we will get a string containing
         * "fortune:" - in this case the old text stays.
         */
        FILE * pipe = NULL;
        if((pipe = popen(FORTUNE_COMMAND,"r")))
        {
            char fortune_buf[FORTUNE_BUF_SIZE];
            int bytes = fread(fortune_buf,1,FORTUNE_BUF_SIZE,pipe);
            if(bytes != 0 && !strstr(fortune_buf,"fortune:"))
            {
                /* Chomp last string */
                char * last_newline = strrchr(fortune_buf,'\n');
                if(last_newline != NULL)
                    last_newline[0] = 0;

                /* Build markup'd string */
                retv = Glib::Markup::escape_text(fortune_buf);
                retv.insert(0,"<span font='10.5' weight='light'>");
                retv.append("</span>");

                for(Glib::ustring::iterator iter = retv.begin(); iter != retv.end(); iter++)
                {
                    /* Erase newline if next char is not a whitespcae,
                     * provides basic formatting for fortunes */
                    Glib::ustring::iterator next = iter;
                    if(*iter == '\n' && !isspace(*(++next)))
                        iter = retv.erase(iter);
                }
            }
            pclose(pipe);
        }
        return retv;
    }
}
