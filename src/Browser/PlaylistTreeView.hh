#ifndef GTKMM_PLAYLISTTREEVIEW_H
#define GTKMM_PLAYLISTTREEVIEW_H

#include <gtkmm.h>
#include "../AbstractBrowser.hh"
#include "../AbstractItemlist.hh"
#include "../MPD/Client.hh"

namespace Browser 
{
    class PlaylistTreeView : public Gtk::Box, public AbstractBrowser, public AbstractItemlist 
    {
        public:
            PlaylistTreeView(MPD::Client& client);
            virtual ~PlaylistTreeView();

            /**
             * @brief Inherited from AbstractBrowser
             *
             * @return a pointer to the widget containing the playlist
             */
            Gtk::Widget * get_container(void);

        private:

            void add_item(void * pSong);
            void clear(void) {}

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

            Glib::ustring m_FilterText;

            /* Treeview related */
            ModelColumns m_Columns;
            Gtk::ScrolledWindow m_ScrolledWindow;
            Gtk::Entry m_Entry;

            /* View of the list */
            Gtk::TreeView m_TreeView;

            /* Actual data */
            Glib::RefPtr<Gtk::ListStore> m_refTreeModel;
            Glib::RefPtr<Gtk::TreeModelFilter> m_refTreeModelFilter;

            /* Selected data */
            Glib::RefPtr<Gtk::TreeSelection> m_TreeSelection;

            /* Client related */
            MPD::Client * mp_Client;
    };
}
#endif //GTKMM_PlaylistTreeView_H
