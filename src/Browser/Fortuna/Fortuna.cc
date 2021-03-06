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
#include "Fortuna.hh"
#include "../../Utils/Utils.hh"

/* Fortuna command: -s -> short text; -n max 500 length */
#define FORTUNE_COMMAND  "fortune -n 350"
#define FORTUNE_BUF_SIZE 1024

namespace Browser
{
Fortuna::Fortuna(Glib::RefPtr<Gtk::Builder>& builder,GManager::BrowserList& list) :
    AbstractBrowser(list,"Fortuna",
                    false, /* Needs connection? */
                    true,  /* Is visible?       */
                    Gtk::Stock::DIALOG_QUESTION)
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

Gtk::Widget * Fortuna::get_container()
{
    return mp_FortuneScroll;
}

/*-----------------------*/

void Fortuna::on_refresh_fortune()
{
    Glib::ustring fortune = get_fortune();
    if(!fortune.empty())
    {
        mp_FortuneLabel->set_markup(fortune);
    }
}

/*-----------------------*/

Glib::ustring Fortuna::get_fortune()
{
    Glib::ustring retv = "";
    /* Open a pipe to the fortune command and read from it,
     * if it isn't installed we will get a string containing
     * "fortune:" - in this case the old text stays.
     */
    FILE * pipe = NULL;
    if((pipe = popen(FORTUNE_COMMAND,"r")))
    {
        char fortune_buf[FORTUNE_BUF_SIZE] = {0 };
        int bytes = fread(fortune_buf,1,FORTUNE_BUF_SIZE,pipe);
        if(bytes != 0 && !strstr(fortune_buf,"fortune:"))
        {
            /* Chomp last string */
            char * last_newline = strrchr(fortune_buf,'\n');
            if(last_newline != NULL)
                last_newline[0] = 0;
            /* Build markup'd string */
            retv = Glib::Markup::escape_text(fortune_buf);
            retv.insert(0,"<b><span color='#111111' font='10.5'>");
            retv.append("</span></b>");
        }
        pclose(pipe);
    }
    return retv;
}
}
