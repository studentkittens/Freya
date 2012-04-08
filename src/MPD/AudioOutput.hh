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
#ifndef FREYA_AUDIOOUTPUT_GUARD
#define FREYA_AUDIOOUTPUT_GUARD

#include "AbstractClientExtension.hh"
#include "AbstractComposite.hh"
#include "../Utils/UseMemPool.hh"

#include <mpd/client.h>

namespace MPD
{
/**
 * @brief Wrapper for mpd_output, implements also two client commands:
 * enable() and disable()
 */
class AudioOutput : public AbstractClientExtension,
    public AbstractComposite,
    public UseMemPool<AudioOutput>
{
public:
    /**
     * @brief You cannot instance this class yourself.
     *
     * @param client
     * @param output
     */
    AudioOutput(MPD::BaseClient& client, mpd_output& output);
    /**
     * @brief Output ID - this is usually not needed
     *
     * @return an unsigned integer, starting from 0
     */
    unsigned get_id();
    /**
     * @brief Get the name of this putput
     *
     * @return a nullterminated string
     */
    const char * get_name();
    /**
     * @brief Obvious.
     *
     * @return
     */
    bool get_enabled();
    /**
     * @brief Enable this output
     *
     * @return true on success
     */
    bool enable();
    /**
     * @brief Disable this output
     *
     * @return true on success
     */
    bool disable();

    /**
     * @brief Alias for get_name() (Implemented due to Compositum)
     *
     * @return
     */
    const char * get_path();

private:
    mpd_output * mp_Output;
};
}

#endif /* end of include guard: FREYA_AUDIOOUTPUT_GUARD */
