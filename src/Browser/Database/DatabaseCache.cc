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
        isFirstStart(true),
        serverChanged(false)
    {}

    /* ------------------------------ */

    DatabaseCache::~DatabaseCache(void)
    {
        clear_cache();
    }

    /* ------------------------------ */

    void DatabaseCache::fill_filelist(AbstractItemlist& data_model, const char * Path)
    {
        /* Get it from the hashmap */
        Glib::ustring peristentPath = Path;
        const CacheVectorType& v = cacheMap[peristentPath];
           
        if(serverChanged)
            clear_cache();

        /* Read in data from client, if not cached yet */
        if(v.empty())
        {
            /* Get files from the server */
            lastVec = const_cast<CacheVectorType*>(&v);
            mp_Client->fill_filelist(*this,Path);
        }

        /* Iterare over the requested stuff, call data_model's add */
        if(!v.empty())
        {
            CacheVectorType::const_iterator iter;
            for(iter = v.begin(); iter != v.end(); iter++)
            {
                const CachePairType& m = (*iter);
                data_model.add_item(m);
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
            if(isFirstStart)
            {
                /* We have no way to check what exactly changed */
                clear_cache();
            }
        }
    }

    /* ------------------------------ */

    void DatabaseCache::on_connection_change(bool server_changed, bool is_connected)
    {
        serverChanged = (isFirstStart) ? false : server_changed;
        isFirstStart = false;
    }

    /* ------------------------------ */
    /*             LOGIC              */
    /* ------------------------------ */

    void DatabaseCache::add_item(AbstractComposite * pItem)
    {
        lastVec->push_back(pItem);
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
                delete m;
            }
        }
        lastVec = NULL;
        cacheMap.clear(); 
    }

    /* ------------------------------ */
}
