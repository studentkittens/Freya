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

    void DatabaseCache::fill_filelist(AbstractFilebrowser& data_model, const char * Path)
    {
        /* Get it from the hashmap */
        Glib::ustring peristentPath = Path;
        const CacheVectorType& v = cacheMap[peristentPath];
           
        /* Read in data from client, if not cached yet */
        if(v.empty())
        {
            /* Get files from the server */
            lastVec = (CacheVectorType*)&v;
            mp_Client->fill_filelist(*this,Path);
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

    void DatabaseCache::on_connection_change(bool server_changed, bool is_connected)
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
