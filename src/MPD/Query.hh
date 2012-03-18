#ifndef FREYA_MPD_DB_QUERY_HH
#define FREYA_MPD_DB_QUERY_HH

#include <mpd/client.h>
#include <vector>

#include "AbstractClientExtension.hh"

namespace MPD
{
    enum QueryType
    {
        QUERY_TAGS,
        QUERY_SONGS
    };

    class BaseClient;
    class Song;

    typedef std::vector<MPD::Song*> SongVector;
    typedef std::vector<char*> TagVector;

    class Query : public AbstractClientExtension
    {
        // Only MPD::BaseClient may instance Queries
        friend class BaseClient;

        public:
            void add_tag_constraint(mpd_tag_type tag, const char * value);
            void add_tag_constraint(const char * tag, const char * value);
            void commit(SongVector &list);
            void commit(TagVector  &list);

            void cancel();

        private:
            Query(MPD::BaseClient& client, QueryType type, int arg);

            mpd_connection * mConn;
            QueryType mType;
    };
}

#endif /* end of include guard: FREYA_MPD_DB_QUERY_HH */

