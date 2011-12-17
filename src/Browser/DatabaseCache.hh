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
            virtual ~DatabaseCache(void);

            /**
             * @brief Same as MPD::Client::fill_filelist(), but gets locally cached data
             *
             * @param data_model 
             * @param path
             */
            void fill_filelist_from_cache(AbstractFilebrowser& data_model, Glib::ustring path);

        private:
   
            typedef std::pair<bool,void*> CachePairType;
            typedef std::vector<CachePairType> CacheVectorType; 
            typedef std::map<Glib::ustring,CacheVectorType> CacheMapType;
    
            /* -------------------------------- */ 

            /* Implemented from AbstractClientUser */
            void on_client_update(mpd_idle event, MPD::NotifyData& data);
            void on_connection_change(bool is_connected);

            /* Implemented from AbstractFilebrowser */
            void add_song_file(MPD::Song * pSong);
            void add_directory(MPD::Directory * pDir);

            /* Logic */
            void clear_cache(void);
            void add_to_cache(CachePairType& pair);

            /* ------------------------------- */

            /* Path is the key, value the song or dir */
            CacheMapType cacheMap;

            /* The last vector used by fill_filelist_from_cache */
            CacheVectorType * lastVec;

            /* Do not clear on first start.. */
            bool is_first_start;
    };
}

#endif /* end of include guard: FREYA_DATABASE_CACHE */
