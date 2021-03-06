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
#include "Song.hh"
#include <iostream>
namespace MPD
{
const char Song::unknown_tag[] = "unknown";

Song::Song(const mpd_song& song) :
    AbstractComposite(true)
{
    mp_Song = (mpd_song*)&song;
}

/*------------------------------*/
Song::Song(const MPD::Song& other) :
    AbstractComposite(true)
{
    mpd_song * other_song = other.mp_Song;
    if(other_song != NULL)
        mp_Song = mpd_song_dup(other_song);
    else
        mp_Song = NULL;
}

/*------------------------------*/

Song::~Song()
{
    if(mp_Song != NULL)
    {
        mpd_song_free(mp_Song);
    }
}

/*------------------------------*/

const char * Song::get_path()
{
    return mpd_song_get_uri(mp_Song);
}
/*------------------------------*/

const char * Song::get_tag(enum mpd_tag_type type, unsigned idx)
{
    const char * tag = mpd_song_get_tag(mp_Song,type,idx);
    return (tag != NULL) ? tag : (type == MPD_TAG_ARTIST) ? get_path() : unknown_tag;
}
/*------------------------------*/

unsigned Song::get_duration()
{
    return mpd_song_get_duration(mp_Song);
}
/*------------------------------*/

time_t Song::get_last_modified()
{
    return mpd_song_get_last_modified(mp_Song);
}
/*------------------------------*/

void Song::set_pos(unsigned pos)
{
    mpd_song_set_pos(mp_Song,pos);
}
/*------------------------------*/

unsigned Song::get_pos()
{
    return mpd_song_get_pos(mp_Song);
}
/*------------------------------*/

unsigned Song::get_id()
{
    return mpd_song_get_id(mp_Song);
}
/*------------------------------*/

Glib::ustring Song::song_format(const char* format, bool markup)
{
    Glib::ustring result(format);
    unsigned n = 0, i = 0;
    const char escape_beg[] = "${",
                              escape_end[] = "}";
    while(n < result.size())
    {
        n = result.find(escape_beg,n);
        i = result.find(escape_end,n);
        if(n >= result.size())
            break;
        /* Split out escape string */
        Glib::ustring tmp = result.substr(n + sizeof(escape_beg) - 1,
                                          i - sizeof(escape_end) - n);
        if(tmp == "artist")
            tmp = get_tag(MPD_TAG_ARTIST,0);
        else if(tmp == "title")
            tmp = get_tag(MPD_TAG_TITLE,0);
        else if(tmp == "album")
            tmp = get_tag(MPD_TAG_ALBUM,0);
        else if(tmp == "track")
            tmp = get_tag(MPD_TAG_TRACK,0);
        else if(tmp == "name")
            tmp = get_tag(MPD_TAG_NAME,0);
        else if(tmp == "date")
            tmp = get_tag(MPD_TAG_DATE,0);
        else if(tmp == "album_artist")
            tmp = get_tag(MPD_TAG_ALBUM_ARTIST,0);
        else if(tmp == "genre")
            tmp = get_tag(MPD_TAG_GENRE,0);
        else if(tmp == "composer")
            tmp = get_tag(MPD_TAG_COMPOSER,0);
        else if(tmp == "performer")
            tmp = get_tag(MPD_TAG_PERFORMER,0);
        else if(tmp == "comment")
            tmp = get_tag(MPD_TAG_COMMENT,0);
        else if(tmp == "disc")
            tmp = get_tag(MPD_TAG_DISC,0);
        else
            tmp="";
        if(markup)
            tmp = Glib::Markup::escape_text(tmp);
        result.replace(n, i - n + (sizeof(escape_end)-1), tmp);
        n += tmp.size() + 1;
    }
    return result;
}
/*------------------------------*/
}
