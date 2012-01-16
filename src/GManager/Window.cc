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
#include "Window.hh"
#include "../Log/Writer.hh"
#include "../Utils/Utils.hh"
#include "../Config/Handler.hh"

namespace GManager
{
    Window::Window(const Glib::RefPtr<Gtk::Builder> &builder)
    {
        main_window=NULL;
        BUILDER_GET_NO_MANAGE(builder,"FreyaMainWindow",main_window);

        main_window->signal_delete_event().connect(sigc::mem_fun(*this,&Window::on_delete_event));

    }

    /*-------------------------*/

    Window::~Window()
    {
        if(main_window!=NULL)
        {
            delete main_window;
            main_window=NULL;
        }
    }

    /*-------------------------*/

    bool Window::on_delete_event(GdkEventAny* event)
    {
        if(CONFIG_GET_AS_INT("settings.trayicon.totrayonclose"))
        {
            main_window->hide();
        }
        else
        {
            Gtk::Main::quit();
        }
        return true;
    }

    /*-------------------------*/

    Gtk::Window* Window::get_window(void)
    {
        return this->main_window;
    }
}
