#ifndef FREYA_BROWSERLIST_GUARD
#define FREYA_BROWSERLIST_GUARD

#include <gtkmm.h>
#include "../AbstractBrowser.hh"

namespace GManager
{
    class BrowserList 
    {
        public:

            BrowserList(const Glib::RefPtr<Gtk::Builder>& builder);
            ~BrowserList();

            void add(AbstractBrowser& browser);

        private:

            void add_name(Glib::ustring& name);

            //Tree model columns:
            class ModelColumns : public Gtk::TreeModel::ColumnRecord
            {
                public:
                    ModelColumns() { add(m_col_name);}
                    Gtk::TreeModelColumn<Glib::ustring> m_col_name;
            };

            // View
            Gtk::TreeView * plugin_listview;

            // Actual model
            Glib::RefPtr<Gtk::ListStore> m_refTreeModel;

            // Model layout
            ModelColumns m_Columns;

            Gtk::Paned * mp_Paned;
    };
}

#endif
