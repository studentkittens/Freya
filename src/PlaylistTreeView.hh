#ifndef GTKMM_PLAYLISTTREEVIEW_H
#define GTKMM_PLAYLISTTREEVIEW_H

#include <gtkmm.h>

namespace GuiLogic
{
    class PlaylistTreeView : public Gtk::Frame
    {
        public:
            PlaylistTreeView(const Glib::RefPtr<Gtk::Builder>& builder);
            virtual ~PlaylistTreeView();

        protected:

            //Tree model columns:
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

            ModelColumns m_Columns;

            Gtk::ScrolledWindow m_ScrolledWindow;
            Gtk::TreeView m_TreeView;
            Glib::RefPtr<Gtk::ListStore> m_refTreeModel;
    };
}
#endif //GTKMM_PlaylistTreeView_H
