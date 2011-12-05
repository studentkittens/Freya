#include "Song.hh"
#include <iostream>
namespace MPD
{
    Song::Song(const mpd_song& song)
    {
        mp_Song = (mpd_song*)&song;
    }
    
    /*------------------------------*/
    
    Song::~Song(void)
    {
        mpd_song_free(mp_Song);
    }

    /*------------------------------*/

    const char * Song::get_uri(void)
    {
        return mpd_song_get_uri(mp_Song);
    }
    /*------------------------------*/

    const char * Song::get_tag(enum mpd_tag_type type, unsigned idx)
    {
        return mpd_song_get_tag(mp_Song,type,idx);

    }
    /*------------------------------*/

    unsigned Song::get_duration(void)
    {
        return mpd_song_get_duration(mp_Song);

    }
    /*------------------------------*/

    time_t Song::get_last_modified(void)
    {
        return mpd_song_get_last_modified(mp_Song);

    }
    /*------------------------------*/

    void Song::set_pos(unsigned pos)
    {
        mpd_song_set_pos(mp_Song,pos);

    }
    /*------------------------------*/

    unsigned Song::get_pos(void)
    {
        return mpd_song_get_pos(mp_Song);

    }
    /*------------------------------*/

    unsigned Song::get_id(void)
    {
        return mpd_song_get_id(mp_Song);
    }
    /*------------------------------*/

    Glib::ustring Song::song_format(const char* format, bool markup)
    {

        Glib::ustring result(format);
        unsigned n=0, i=0;

        while(n<result.size())
        {
            n=result.find_first_of("${",n);
            i=result.find_first_of("}",n);
            if(n>=result.size())
                continue;
            Glib::ustring tmp = result.substr(n+2,i-n-2);
            /* GESCHACHTELT WUAHAHAHAHAHAH SCNR, ich fixe das spaeter noch, keine angst, war nur zu faul und wollte etwas provozieren :P*/
            tmp=
                 tmp=="artist"?get_tag(MPD_TAG_ARTIST,0)!=NULL?get_tag(MPD_TAG_ARTIST,0):"unknown":
                 tmp=="title"?get_tag(MPD_TAG_TITLE,0)!=NULL?get_tag(MPD_TAG_TITLE,0):get_uri():
                 tmp=="album"?get_tag(MPD_TAG_ALBUM,0)!=NULL?get_tag(MPD_TAG_ALBUM,0):"unknown":
                 tmp=="track"?get_tag(MPD_TAG_TRACK,0)!=NULL?get_tag(MPD_TAG_TRACK,0):"unknown":
                 tmp=="name"?get_tag(MPD_TAG_NAME,0)!=NULL?get_tag(MPD_TAG_NAME,0):"unknown":
                 tmp=="date"?get_tag(MPD_TAG_DATE,0)!=NULL?get_tag(MPD_TAG_DATE,0):"unknown":
                 tmp=="album_artist"?get_tag(MPD_TAG_ALBUM_ARTIST,0)!=NULL?get_tag(MPD_TAG_ALBUM_ARTIST,0):"unknown":
                 tmp=="genre"?get_tag(MPD_TAG_GENRE,0)!=NULL?get_tag(MPD_TAG_GENRE,0):"unknown":
                 tmp=="composer"?get_tag(MPD_TAG_COMPOSER,0)!=NULL?get_tag(MPD_TAG_COMPOSER,0):"unknown":
                 tmp=="performer"?get_tag(MPD_TAG_PERFORMER,0)!=NULL?get_tag(MPD_TAG_PERFORMER,0):"unknown":
                 tmp=="comment"?get_tag(MPD_TAG_COMMENT,0)!=NULL?get_tag(MPD_TAG_COMMENT,0):"unknown":
                 tmp=="disc"?get_tag(MPD_TAG_DISC,0)!=NULL?get_tag(MPD_TAG_DISC,0):"unknown":" "

            ;

            /* SCHOEN ODER? ODEEERRRRRR?! D: */


            if(markup)
            {
                tmp=Glib::Markup::escape_text(tmp);
            }
            result.replace(n,i-n+1,tmp);
            n=i;
            n++;
        }


        return result;
    }
    /*------------------------------*/
    Glib::ustring Song::song_format(const char* format)
    {
        return song_format(format,true);
    }
    /*------------------------------*/
}
