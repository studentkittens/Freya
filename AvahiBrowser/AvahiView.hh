#ifndef FREYA_AVAHIVIEW_H
#define FREYA_AVAHIVIEW_H

#include <gtkmm.h>

class FreyaAvahiView : public Gtk::Window
{
    public:
        FreyaAvahiView(void);
        virtual ~FreyaAvahiView(void);
        
        void server_append(const char * ip, const char * hostname, const char * name, unsigned int port);
        void server_delete(const char * name);
        void set_status(const char * message);

    protected:
        //Signal handlers:
        void on_button_cancel();
        void on_button_select();

    //Tree model columns:
    class ModelColumns : public Gtk::TreeModel::ColumnRecord
    {
        public:

            ModelColumns()
            { add(m_col_ip); add(m_col_hostname); add(m_col_name); add(m_col_port);}

            Gtk::TreeModelColumn<Glib::ustring> m_col_ip;
            Gtk::TreeModelColumn<Glib::ustring> m_col_hostname;
            Gtk::TreeModelColumn<Glib::ustring> m_col_name;
            Gtk::TreeModelColumn<unsigned int>  m_col_port;
    };

        ModelColumns m_Columns;

        //Child widgets:
        Gtk::VBox m_VBox;

        Gtk::ScrolledWindow m_ScrolledWindow;
        Gtk::TreeView m_TreeView;
        Glib::RefPtr<Gtk::ListStore> m_refTreeModel;

        Gtk::HButtonBox m_ButtonBox;
        Gtk::Button m_Button_Cancel;
        Gtk::Button m_Button_Select;
        Gtk::Label  m_Status_Label;

    private:

        unsigned int server_counter;
};

#endif //GTKMM_FREYAAVAHIVIEW_H
