#ifndef FREYA_QUEUE_MERGER
#define FREYA_QUEUE_MERGER

#include "../AbstractItemlist.hh"
#include "../AbstractClientUser.hh"
#include "QueueModelColumns.hh"

#include <gtkmm.h>

namespace Browser 
{
    class QueueMerger : public AbstractItemlist, public AbstractClientUser
    {
        public:
            QueueMerger(MPD::Client& client,
                        Glib::RefPtr<Gtk::ListStore>& queue_model,
                        QueueModelColumns& queue_columns);

            /**
             * @brief 
             *
             * @param pSong
             */
            void add_item(void * pSong);

            void disable_merge_once(void);
            void recalculate_positions(unsigned pos = 0);

        private:
            
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
             * @param is_connected
             */
            void on_connection_change(bool is_connected);

            /**
             * @brief Set the contents of a single row
             *
             * @param row
             * @param pSong
             */
            void set_row_contents(Gtk::TreeModel::Row& row, MPD::Song * pSong);

            void add_row(MPD::Song * pSong);

            void merge(MPD::Song * pSong);

            void trim(unsigned starting_with);


            Gtk::TreeModel::iterator get_iter_at_pos(int pos);

            /* -------------------- */

            bool mergeDisabled;
            bool needsRefill;
            bool mergeIterIsValid;

            Gtk::TreeModel::iterator mergeIter;

            unsigned lastPlaylistVersion;
            unsigned playlistLength;
            unsigned mergePos;

            Glib::RefPtr<Gtk::ListStore> mp_QueueModel;
            QueueModelColumns * mp_QueueColumns;
    };
}

#endif /* end of include guard: FREYA_QUEUE_MERGER */
