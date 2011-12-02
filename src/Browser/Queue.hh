#ifndef FREYA_QUEUE_H
#define FREYA_QUEUE_H

#include <gtkmm.h>
#include "../AbstractBrowser.hh"
#include "../AbstractItemlist.hh"
#include "../AbstractClientUser.hh"
#include "../MPD/Client.hh"
#include "QueuePopup.hh"

namespace Browser 
{
    class Queue : public AbstractBrowser, public AbstractItemlist, public AbstractClientUser
    {
        public:
            Queue(MPD::Client& client, Glib::RefPtr<Gtk::Builder>& builder);
            virtual ~Queue();

            /**
             * @brief Inherited from AbstractBrowser
             *
             * @return a pointer to the widget containing the playlist
             */
            Gtk::Widget * get_container(void);

        private:

            /* Implemtend from AbstractItemlist */
            void add_item(void * pSong);

            /* Implemented from AbstractClientUser */
            void on_client_update(enum mpd_idle event, MPD::NotifyData& data);
            void on_connection_change(bool is_connected);

            /* Menuhandling */
            void on_menu_clear_clicked(void);
            void on_menu_remove_clicked(void);
            void on_menu_add_to_pl_clicked(void);

            /* Other */
            void on_row_activated(const Gtk::TreeModel::Path& path, Gtk::TreeViewColumn* column);
            bool on_filter_row_visible(const Gtk::TreeModel::const_iterator& iter);
            void on_entry_activate(void);

            /* Tree model columns: */
            class ModelColumns : public Gtk::TreeModel::ColumnRecord
            {
                public:

                    ModelColumns()
                    { add(m_col_id); add(m_col_artist); add(m_col_album); add(m_col_title); }

                    Gtk::TreeModelColumn<unsigned int>  m_col_id;
                    Gtk::TreeModelColumn<Glib::ustring> m_col_title;
                    Gtk::TreeModelColumn<Glib::ustring> m_col_album;
                    Gtk::TreeModelColumn<Glib::ustring> m_col_artist;
            };

            /* Members */

            Glib::ustring m_FilterText;

            /* Treeview related */
            ModelColumns m_Columns;

            /* View of the list */
            Gtk::TreeView * mp_TreeView;

            /* Actual data */
            Glib::RefPtr<Gtk::ListStore> m_refTreeModel;
            Glib::RefPtr<Gtk::TreeModelFilter> m_refTreeModelFilter;

            /* Selected data */
            Glib::RefPtr<Gtk::TreeSelection> m_TreeSelection;

            /* Popup */
            QueuePopup * mp_Popup;
            
            /* other widgets */
            Gtk::Entry * mp_Entry;
            Gtk::Box * mp_QueueBox;
    };
}
#endif //FREYA_QUEUE_H
