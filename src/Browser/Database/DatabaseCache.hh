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

#include "../../MPD/AbstractClientUser.hh"
#include "../../MPD/AbstractItemlist.hh"

namespace Browser
{
    /**
     * @brief Acts as a Proxy betwenn Browser::Database and MPD::Client, but caches requested data
     *
     * Note: It is actually a Proxy FOR MPD::Client, but used by Browser::Database.
     *
     * Once the Database requests a list of files for a certain path, a hashmap is looked up if it's already
     * cached, if not DatabaseCache asks the client for the filelist.
     *
     * As Hashmap a std::map was used, with the Path as key and a vector of values as Hashvalue.
     */
    class DatabaseCache :
        public MPD::AbstractClientUser,
        public MPD::AbstractItemlist,
        public MPD::AbstractItemGenerator
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
        void fill_filelist(MPD::AbstractItemlist& data_model, const char * path);

        /**
         * @brief Implemented from AbstractItemlist
         *
         * You are not supposed to call this yourself.
         *
         * @param pItem
         */
        void add_item(MPD::AbstractComposite * pItem);

        /* Method stubs .. */
        void fill_queue(MPD::AbstractItemlist& data_model) {}
        void fill_queue_changes(MPD::AbstractItemlist& data_model, unsigned last_version, unsigned& first_pos) {}
        void fill_playlists(MPD::AbstractItemlist& data_model) {}
        void fill_outputs(MPD::AbstractItemlist& data_model) {}


    private:

        /**
         * @brief The actual value
         *
         * First bool is true if it's a file,
         * void* points to the actual data. Cast when necessary.
         */
        typedef MPD::AbstractComposite* CachePairType;
        /**
         * @brief The list of actual values
         */
        typedef std::vector<CachePairType> CacheVectorType;
        /**
         * @brief The Hashmap, The path is used as key value, default comparator is used
         */
        typedef std::map<Glib::ustring,CacheVectorType> CacheMapType;

        /* -------------------------------- */

        /**
         * @brief Implemented from AbstractClientUser
         *
         * @param event
         * @param data
         */
        void on_client_update(mpd_idle event, MPD::NotifyData& data);
        /**
         * @brief Implemented from AbstractClientUser
         *
         * @param server_changed
         * @param is_connected
         */
        void on_connection_change(bool server_changed, bool is_connected);

        /* Logic */
        void clear_cache(void);

        /* ------------------------------- */

        /* Path is the key, value the song or dir */
        CacheMapType cacheMap;

        /* The last vector used by fill_filelist */
        CacheVectorType * lastVec;

        /* Do not clear on first start.. */
        bool isFirstStart;
        bool serverChanged;
    };
}

#endif /* end of include guard: FREYA_DATABASE_CACHE */
