#ifndef FREYA_DATABASE_FOGI85CP
#define FREYA_DATABASE_FOGI85CP

#include <gtkmm.h>
#include "../AbstractBrowser.hh"
#include "../AbstractSonglist.hh"
#include "../MPD/Client.hh"

namespace Browser
{
    /* Does not inherig from frame this time */
    class DatabaseBrowser : public AbstractBrowser
    {
        public:
            DatabaseBrowser(MPD::Client& client, Glib::RefPtr<Gtk::Builder>& builder);
            virtual ~DatabaseBrowser();
            Gtk::Widget * get_container(void);

        private:

            class ModelColumns : public Gtk::TreeModel::ColumnRecord
            {
                public:
                    ModelColumns()
                    { add(m_col_name); add(m_col_icon); }
                    Gtk::TreeModelColumn<Glib::ustring> m_col_name;
                    Gtk::TreeModelColumn<Glib::RefPtr<Gdk::Pixbuf>>  m_col_icon;
            };

            Gtk::IconView * mp_IView;
            Gtk::Box * mp_ParentBox;
            Gtk::Button * mp_HomeButton, * mp_DirUpButton;
            Gtk::Label * mp_StatusLabel;

            ModelColumns m_Columns;
            Glib::RefPtr<Gtk::ListStore> m_DirStore;
            MPD::Client * mp_Client;

            Glib::RefPtr<Gdk::Pixbuf> m_FileIcon, m_DirIcon;
    };
}

#endif /* end of include guard: DATABASE_FOGI85CP */
