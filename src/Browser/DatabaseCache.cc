#include "DatabaseCache.hh"

namespace Browser
{
    /* ----------------------------- */

    DatabaseCache::DatabaseCache(MPD::Client& client) : 
        AbstractClientUser(client),
        lastVec(NULL)
    {}

    /* ------------------------------ */

    DatabaseCache::~DatabaseCache(void)
    {
        clear_cache();
    }

    /* ------------------------------ */

    void DatabaseCache::fill_filelist_from_cache(AbstractFilebrowser& data_model, Glib::ustring Path)
    {
        /* Get it from the hashmap */
        const std::vector<DatabaseCacheModel>& v = cacheMap[Path];

        /* Read in data from clientm, if not cached yet */
        if(v.empty())
        {
            /* Dirty cast :-( */
            lastVec = (std::vector<DatabaseCacheModel>*)&v;

            /* Get files from the server */
            mp_Client->fill_filelist(*this,Path.c_str());
        }

        /* Iterare over the requested stuff, call data_model's add */
        if(!v.empty())
        {
            std::vector<DatabaseCacheModel>::const_iterator iter;
            for(iter = v.begin(); iter != v.end(); iter++)
            {
                const DatabaseCacheModel& m = (*iter);
                if(m.is_file)
                {
                    data_model.add_song_file((MPD::Song*)m.store);
                }
                else
                {
                    data_model.add_directory((MPD::Directory*)m.store);
                }
            }
        }
    }

    /*            PRIVATE             */
    /* ------------------------------ */

    void DatabaseCache::on_client_update(mpd_idle event, MPD::NotifyData& data)
    {
        if(event & MPD_IDLE_DATABASE)
        {
            /* We have no way to check what exactly changed */
            clear_cache();
        }
    }

    /* ------------------------------ */

    void DatabaseCache::on_connection_change(bool is_connected)
    {}

    /*             LOGIC              */
    /* ------------------------------ */
    
    void DatabaseCache::add_to_cache(bool is_file, void * pData)
    {
        DatabaseCacheModel m;
        m.is_file = is_file;
        m.store   = pData;
        lastVec->push_back(m);
    }
    
    /* ------------------------------ */

    void DatabaseCache::add_song_file(MPD::Song * pSong)
    {
        add_to_cache(true,pSong);
    }

    /* ------------------------------ */

    void DatabaseCache::add_directory(MPD::Directory * pDir)
    {
        add_to_cache(false,pDir);
    }

    /* ------------------------------ */

    void DatabaseCache::clear_cache(void)
    {
        CacheMapType::const_iterator iter;
        for(iter = cacheMap.begin(); iter != cacheMap.end(); iter++)
        {
            const std::vector<DatabaseCacheModel>& v = (*iter).second;
            std::vector<DatabaseCacheModel>::const_iterator vec_iter;

            for(vec_iter = v.begin(); vec_iter != v.end(); vec_iter++)
            {
                const DatabaseCacheModel& m = (*vec_iter);
                if(m.is_file)
                {
                    MPD::Song * to_delete = (MPD::Song*)m.store;
                    delete to_delete;
                }
                else
                {
                    MPD::Directory * to_delete = (MPD::Directory*)m.store;
                    delete to_delete;
                }
            }
        }
        lastVec = NULL;
        cacheMap.clear(); 
    }

    /* ------------------------------ */
}
