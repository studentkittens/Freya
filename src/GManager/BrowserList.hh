#ifndef FREYA_BROWSERLIST_GUARD
#define FREYA_BROWSERLIST_GUARD

#include <gtkmm.h>
#include "../AbstractBrowser.hh"
#include "../AbstractClientUser.hh"

namespace GManager
{
    class BrowserList : public AbstractClientUser
    {
        public:

            BrowserList(MPD::Client& client, const Glib::RefPtr<Gtk::Builder>& builder);

            /**
             * @brief Add the browser to the list and manage it
             *
             * @param browser A user class that inherits from AbstractBrowser
             */
            void add(AbstractBrowser& browser);

        private:

            void change_browser(AbstractBrowser * browser);
            void on_selection_changed(void);

            /* Fortunes :-) */
            Glib::ustring get_fortune(void);

            void on_client_update(enum mpd_idle type, MPD::NotifyData& data);
            void on_connection_change(bool is_connected);
            void on_refresh_fortune(void);

            /* Tree model columns: */
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

            /* Browserlist widget, where all browser stuff is happening in */
            Gtk::Box * mp_List;
            
            /* fortune label on startup */
            Gtk::Label * mp_FortuneLabel;
    };
}

#endif
