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
#include "AudioOutput.hh"
namespace MPD
{
    AudioOutput::AudioOutput(MPD::BaseClient& client, mpd_output& output) : 
        AbstractClientExtension(client)
    {
        mp_Output = &output;
    }

    /* ----------------- */
    
    unsigned AudioOutput::get_id(void)
    {
        return mpd_output_get_id(mp_Output); 
    }

    const char * AudioOutput::get_name(void)
    {
        return mpd_output_get_name(mp_Output);
    }

    bool AudioOutput::get_enabled(void)
    {
        return mpd_output_get_enabled(mp_Output);
    }

    //-----------------------
    // CLIENT EXTENSIONS
    //-----------------------    

    bool AudioOutput::enable(void)
    {
        bool retv = false;
        unsigned id = get_id();

        EXTERNAL_GET_BUSY 
        {
            retv = mpd_run_enable_output(conn,id);
        }
        EXTERNAL_GET_LAID

        return retv;
    }

    bool AudioOutput::disable(void)
    {
        bool retv = false;
        unsigned id = get_id();

        EXTERNAL_GET_BUSY 
        {
            retv = mpd_run_disable_output(conn,id);
        }
        EXTERNAL_GET_LAID

        return retv;
    }
}
