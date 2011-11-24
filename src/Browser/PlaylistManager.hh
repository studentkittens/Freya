#ifndef PLAYLISTMANAGER_LUYIHGVL
#define PLAYLISTMANAGER_LUYIHGVL

#include <gtkmm.h>
#include "../AbstractBrowser.hh"
#include "../AbstractItemlist.hh"
#include "../MPD/Client.hh"
#include "../MPD/Playlist.hh"

namespace Browser 
{
    class PlaylistManager : public Gtk::Frame, public AbstractBrowser, public AbstractItemlist
    {
        public:
            PlaylistManager(MPD::Client& client, Glib::RefPtr<Gtk::Builder>& builder);
            virtual ~PlaylistManager();

            /**
             * @brief Inherited from AbstractBrowser
             *
             * @return a pointer to the widget containing the playlist
             */
            Gtk::Widget * get_container(void);

        private:

            void add_item(void * pPlaylist);
            void clear(void) {}

            /* Tree model columns: */
            class ModelColumns : public Gtk::TreeModel::ColumnRecord
            {
                public:

                    ModelColumns()
                    { add(m_col_plist); add(m_col_name); add(m_col_num_songs); add(m_col_last_modfied); }
                    Gtk::TreeModelColumn<MPD::Playlist*> m_col_plist;
                    Gtk::TreeModelColumn<Glib::ustring> m_col_name;
                    Gtk::TreeModelColumn<unsigned> m_col_num_songs;
                    Gtk::TreeModelColumn<Glib::ustring> m_col_last_modfied;
            };

            /* Treeview related */
            ModelColumns m_Columns;

            Gtk::TreeView * mp_TreeView;
            Glib::RefPtr<Gtk::ListStore> m_refTreeModel;

            /* Client related */
            MPD::Client * mp_Client;
    };
}

#endif /* end of include guard: PLAYLISTMANAGER_LUYIHGVL */
