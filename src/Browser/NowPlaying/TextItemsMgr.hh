#ifndef FREYA_TEXTITEMSMGR_HH
#define FREYA_TEXTITEMSMGR_HH

#include <gtkmm.h>
#include "../../Glyr/UpdateInterface.hh"

/*
 * Instance the Manager from the glade file,
 * any other instancing is done by the manager itself,
 * also remember a pointer to the manager, so we can update
 * it later.
 */
#define ADD_MANAGER(builder, name, interface)        \
        BUILDER_GET_DERIVED(builder,name,interface); \
        managerList.push_back(interface);            \

namespace Browser 
{
    typedef std::vector<Glyr::UpdateInterface*> ManagerVector;

    class TextItemsMgr : public Gtk::Expander, public Glyr::UpdateInterface
    {
        public:

            TextItemsMgr(BaseObjectType* cobject, const Glib::RefPtr<Gtk::Builder>& builder);
            void update(MPD::Client& client, mpd_idle event, MPD::NotifyData& data);

        protected:

            void on_type_combo_changed();
            void add_txtview_page(const Glib::RefPtr<Gtk::Builder>& builder,const char * name,Gtk::StockID icon);

        private:

            Gtk::Notebook * mp_NBook;
            Gtk::ComboBox * mp_TypeSelection;

            /* 
             * Text pages
             */
            ManagerVector managerList;

            /* 
             * Model for the combobox
             */
            class TypeModelColumns : public Gtk::TreeModel::ColumnRecord {
                public:
                    TypeModelColumns() {
                        add(m_col_id);
                        add(m_col_icon);
                    }
                    Gtk::TreeModelColumn<Glib::ustring> m_col_id;
                    Gtk::TreeModelColumn< Glib::RefPtr<Gdk::Pixbuf>> m_col_icon;
            };
            TypeModelColumns m_TypeColumns;
            Glib::RefPtr<Gtk::ListStore> m_TypeModel;
    };
}

#endif /* end of include guard: FREYA_TEXTITEMSMGR_HH*/
