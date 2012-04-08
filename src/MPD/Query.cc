#include "Query.hh"
#include "BaseClient.hh"

#include <glib.h>

#include "../Log/Writer.hh"

namespace MPD
{
Query::Query(MPD::BaseClient& client, QueryType type, int arg) :
    AbstractClientExtension(client),
    mType(type)
{
    g_assert(get_c_connection());
    switch(type)
    {
    case QUERY_SONGS:
        mpd_search_db_songs(get_c_connection(),(bool)arg);
        break;
    case QUERY_TAGS:
        mpd_search_db_tags(get_c_connection(),(mpd_tag_type)arg);
        break;
    default:
        Warning("Unknown QUERY_TYPE - this is a bug.");
    }
}

//////////////////////////////

void Query::add_tag_constraint(mpd_tag_type tag, const char * value)
{
    mpd_search_add_tag_constraint(get_c_connection(),MPD_OPERATOR_DEFAULT,tag,value);
}

//////////////////////////////

void Query::add_tag_constraint(const char * tag, const char * value)
{
    add_tag_constraint(mpd_tag_name_iparse(tag),value);
}

//////////////////////////////

void Query::cancel()
{
    mpd_search_cancel(get_c_connection());
}

//////////////////////////////

void Query::commit(SongVector &list)
{
    if(mType == QUERY_SONGS)
    {
        EXTERNAL_GET_BUSY
        {
            mpd_connection * conn = get_c_connection();
            if(mpd_search_commit(conn))
            {
                mpd_song * csong;
                while((csong = mpd_recv_song(conn)))
                {
                    list.push_back(new MPD::Song(*csong));
                }
            }
        }
        EXTERNAL_GET_LAID
    }
    else
    {
        Warning("Only pass a SongVector to Query::commit() if it was created with create_db_songs_query()");
    }
}

//////////////////////////////

void Query::commit(TagVector &list)
{
    if(mType == QUERY_TAGS)
    {
        EXTERNAL_GET_BUSY
        {
            mpd_connection * conn = get_c_connection();
            if(mpd_search_commit(conn))
            {
                mpd_pair * pair;
                while((pair = mpd_recv_pair(conn)))
                {
                    list.push_back(g_strdup(pair->value));
                    mpd_return_pair(conn,pair);
                }
            }
        }
        EXTERNAL_GET_LAID
    }
    else
    {
        Warning("Only pass a TagVector to Query::commit() if it was created with create_db_tag_query()");
    }
}
}
