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

            /**
             * @brief Add the browser to the list and manage it
             *
             * @param browser A user class that inherits from AbstractBrowser
             */
            void add(AbstractBrowser& browser);

        private:

            void change_browser(AbstractBrowser * browser);
            void on_selection_changed(void);
            Glib::ustring get_fortune(void);

            //Tree model columns:
            class ModelColumns : public Gtk::TreeModel::ColumnRecord
            {
                public:
                    ModelColumns() { add(m_col_name); add(m_col_icon); add(m_col_browser); }
                    Gtk::TreeModelColumn<Glib::ustring> m_col_name;
                    Gtk::TreeModelColumn<Glib::RefPtr<Gdk::Pixbuf>> m_col_icon;
                    Gtk::TreeModelColumn<AbstractBrowser*> m_col_browser;
            };

            /* View */
            Gtk::TreeView * mp_PluginListview;

            /* Actual model */
            Glib::RefPtr<Gtk::ListStore> m_refTreeModel;

            /* Model layout */
            ModelColumns m_Columns;

            /* Selected data of model */
            Glib::RefPtr<Gtk::TreeSelection> m_TreeSelection;

            /* Paned widgets, where all browser stuff is happening in */
            Gtk::Box * mp_Paned;
    };
}

#endif
