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
#ifndef FREYA_AUDIOOUTPUT_GUARD
#define FREYA_AUDIOOUTPUT_GUARD

#include "AbstractClientExtension.hh"

namespace MPD
{
    typedef struct mpd_output mpd_output;

    class AudioOutput : AbstractClientExtension 
    {
        public:
            AudioOutput(MPD::BaseClient& client, mpd_output& output);
            unsigned get_id(void);
            const char * get_name(void);
            bool get_enabled(void);
            bool enable(void);
            bool disable(void);

        private:
            mpd_output * mp_Output;
    };
}

#endif /* end of include guard: FREYA_AUDIOOUTPUT_GUARD */
