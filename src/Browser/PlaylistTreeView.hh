#ifndef GTKMM_PLAYLISTTREEVIEW_H
#define GTKMM_PLAYLISTTREEVIEW_H

#include <gtkmm.h>
#include "../AbstractBrowser.hh"
#include "../AbstractSonglist.hh"
#include "../MPD/Client.hh"

namespace Browser 
{
    class PlaylistTreeView : public Gtk::Box, public AbstractBrowser, public AbstractSonglist 
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

            bool add_song(MPD::Song * new_song);

            /* Tree model columns: */
            class ModelColumns : public Gtk::TreeModel::ColumnRecord
            {
                public:

                    ModelColumns()
                    { add(m_col_id); add(m_col_title); add(m_col_album); add(m_col_artist); }

                    Gtk::TreeModelColumn<unsigned int>  m_col_id;
                    Gtk::TreeModelColumn<Glib::ustring> m_col_title;
                    Gtk::TreeModelColumn<Glib::ustring> m_col_album;
                    Gtk::TreeModelColumn<Glib::ustring> m_col_artist;
            };

            /* Treeview related */
            ModelColumns m_Columns;
            Gtk::ScrolledWindow m_ScrolledWindow;
            Gtk::TreeView m_TreeView;
            Gtk::Entry m_Entry;
            Glib::RefPtr<Gtk::ListStore> m_refTreeModel;

            /* Client related */
            MPD::Client * mp_Client;
    };
}
#endif //GTKMM_PlaylistTreeView_H
