#ifndef FREYA_DATABASE_CACHE
#define FREYA_DATABASE_CACHE

#include "../MPD/AbstractClientUser.hh"
#include "../MPD/AbstractFilebrowser.hh"

namespace Browser
{
    class DatabaseCache : public AbstractClientUser, public AbstractFilebrowser
    {
        public:
            DatabaseCache(MPD::Client& client);
            ~DatabaseCache(void);

            /**
             * @brief Same as MPD::Client::fill_filelist(), but gets locally cached data
             *
             * @param data_model 
             * @param path
             */
            void fill_filelist_from_cache(AbstractFilebrowser& data_model, Glib::ustring path);

        private:
    
            /* Actual stored data.
             * One type, so it can be stored as std::map, 
             * std::pair would do it for the moment here too though.
             */
            struct DatabaseCacheModel
            {
                bool is_file;
                void * store;
            };

            /* Implemented from AbstractClientUser */
            void on_client_update(mpd_idle event, MPD::NotifyData& data);
            void on_connection_change(bool is_connected);

            /* Implemented from AbstractFilebrowser */
            void add_song_file(MPD::Song * pSong);
            void add_directory(MPD::Directory * pDir);

            /* Logic */
            void clear_cache(void);
            void add_to_cache(bool is_file, void * pData);

            /* ------------------------------- */

            typedef std::map<Glib::ustring,std::vector<DatabaseCacheModel>> CacheMapType;

            /* Path is the key, value the song or dir */
            CacheMapType cacheMap;

            /* The last vector used by fill_filelist_from_cache */
            std::vector<DatabaseCacheModel> * lastVec;

    };
}

#endif /* end of include guard: FREYA_DATABASE_CACHE */
