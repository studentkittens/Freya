#ifndef FREYA_TEXTITEMSMGR_HH
#define FREYA_TEXTITEMSMGR_HH

#include <gtkmm.h>

namespace Browser 
{
    class TextItemsMgr : public Gtk::Expander
    {
        public:
            TextItemsMgr(BaseObjectType* cobject, const Glib::RefPtr<Gtk::Builder>& builder);

        protected:

            void on_type_combo_changed();
            void add_txtview_page(const Glib::RefPtr<Gtk::Builder>& builder,const char * name,Gtk::StockID icon);

        private:

            Gtk::Notebook * mp_NBook;
            Gtk::ComboBox * mp_TypeSelection;

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
