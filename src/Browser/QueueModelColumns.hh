#ifndef FREYA_QUEUEMODELCOLUMNS_GUARD
#define FREYA_QUEUEMODELCOLUMNS_GUARD

#include <gtkmm.h>

namespace Browser
{
    /* Tree model columns: */
    class QueueModelColumns : public Gtk::TreeModel::ColumnRecord
    {
        public:

            QueueModelColumns();

            Gtk::TreeModelColumn<unsigned>      m_col_id;
            Gtk::TreeModelColumn<unsigned>      m_col_pos;
            Gtk::TreeModelColumn<Glib::ustring> m_col_title;
            Gtk::TreeModelColumn<Glib::ustring> m_col_album;
            Gtk::TreeModelColumn<Glib::ustring> m_col_artist;
    };
}

#endif /* end of include guard: FREYA_QUEUEMODELCOLUMNS_GUARD */
