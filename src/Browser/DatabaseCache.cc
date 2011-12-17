#include "DatabaseCache.hh"

namespace Browser
{
    /* ----------------------------- */

    DatabaseCache::DatabaseCache(MPD::Client& client) : 
        AbstractClientUser(client),
        lastVec(NULL),
        is_first_start(true)
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
        const CacheVectorType& v = cacheMap[Path];
           
        /* Read in data from client, if not cached yet */
        if(v.empty())
        {
            /* Get files from the server */
            lastVec = (CacheVectorType*)&v;
            mp_Client->fill_filelist(*this,Path.c_str());
        }

        /* Iterare over the requested stuff, call data_model's add */
        if(!v.empty())
        {
            CacheVectorType::const_iterator iter;
            for(iter = v.begin(); iter != v.end(); iter++)
            {
                const CachePairType& m = (*iter);

                /* Is it a file? */
                if(m.first)
                    data_model.add_song_file((MPD::Song*)m.second);
                else
                    data_model.add_directory((MPD::Directory*)m.second);
            }
        }
    }

    /* ------------------------------ */
    /*            PRIVATE             */
    /* ------------------------------ */

    void DatabaseCache::on_client_update(mpd_idle event, MPD::NotifyData& data)
    {
        if(event & MPD_IDLE_DATABASE)
        {
            if(!is_first_start)
            {
                /* We have no way to check what exactly changed */
                clear_cache();
            }
            is_first_start = false;
        }
    }

    /* ------------------------------ */

    void DatabaseCache::on_connection_change(bool is_connected)
    {}

    /* ------------------------------ */
    /*             LOGIC              */
    /* ------------------------------ */

    void DatabaseCache::add_to_cache(CachePairType& pair)
    {
        lastVec->push_back(pair);
    }

    /* ------------------------------ */

    void DatabaseCache::add_song_file(MPD::Song * pSong)
    {
        CachePairType m(true,pSong);
        add_to_cache(m);
    }

    /* ------------------------------ */

    void DatabaseCache::add_directory(MPD::Directory * pDir)
    {
        CachePairType m(false,pDir);
        add_to_cache(m);
    }

    /* ------------------------------ */

    void DatabaseCache::clear_cache(void)
    {
        CacheMapType::const_iterator iter;
        for(iter = cacheMap.begin(); iter != cacheMap.end(); iter++)
        {
            const CacheVectorType& v = iter->second;
            CacheVectorType::const_iterator vec_iter;

            for(vec_iter = v.begin(); vec_iter != v.end(); vec_iter++)
            {
                const CachePairType& m = (*vec_iter);
                if(m.first)
                    delete (MPD::Song*)m.second;
                else
                    delete (MPD::Directory*)m.second;
            }
        }
        lastVec = NULL;
        cacheMap.clear(); 
    }

    /* ------------------------------ */
}
