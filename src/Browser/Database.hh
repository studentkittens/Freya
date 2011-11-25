#ifndef FREYA_DATABASE_FOGI85CP
#define FREYA_DATABASE_FOGI85CP

#include <gtkmm.h>
#include "../AbstractBrowser.hh"
#include "../AbstractItemlist.hh"
#include "../MPD/Client.hh"
#include "../MPD/Directory.hh"

namespace Browser
{
    /* Does not inherig from frame this time */
    class DatabaseBrowser : public AbstractBrowser, public AbstractFilebrowser 
    {
        public:
            DatabaseBrowser(MPD::Client& client, Glib::RefPtr<Gtk::Builder>& builder);
            virtual ~DatabaseBrowser();

            Gtk::Widget * get_container(void);
            void add_directory(MPD::Directory * pDir);
            void add_song_file(MPD::Song * pSong);

        private:

            void on_item_activated(const Gtk::TreeModel::Path& path);
            void on_home_button_clicked(void);
            void set_current_path(const char * path);
            void go_one_up(void);
            void add_item(const char * path, bool is_file);

            class ModelColumns : public Gtk::TreeModel::ColumnRecord
            {
                public:
                    ModelColumns()
                    { add(m_col_path); add(m_col_name); add(m_col_icon); add(m_col_is_file); }
                    Gtk::TreeModelColumn<Glib::ustring> m_col_name;
                    Gtk::TreeModelColumn<Glib::ustring> m_col_path;
                    Gtk::TreeModelColumn<Glib::RefPtr<Gdk::Pixbuf>> m_col_icon;
                    Gtk::TreeModelColumn<bool> m_col_is_file;
            };

            /* Actual widgets */
            Gtk::IconView * mp_IView;
            Gtk::Box * mp_ParentBox;
            Gtk::Button * mp_HomeButton, * mp_DirUpButton;
            Gtk::Label * mp_StatusLabel;
            Glib::RefPtr<Gdk::Pixbuf> m_FileIcon, m_DirIcon;

            /* Models behind */
            ModelColumns m_Columns;
            Glib::RefPtr<Gtk::TreeSelection> m_Selection;
            Glib::RefPtr<Gtk::ListStore> m_DirStore;
            MPD::Client * mp_Client;

            /* The current path shown (NULL for root) */
            std::string mp_Path;
    };
}

#endif /* end of include guard: DATABASE_FOGI85CP */
