#include <gtkmm.h>
#include <stdlib.h>
#include <iostream>

#include "PlaylistTreeView.hh"

#include "MPD/Client.hh"

using namespace std;

Gtk::Scale * time_scale = NULL;

gboolean do_time_scale_step(void)
{
    time_scale->set_value(time_scale->get_value() + 1.0);
    return TRUE;
}
  
//Tree model columns:
class ModelColumns : public Gtk::TreeModel::ColumnRecord
{
    public:
        ModelColumns() { add(m_col_name);}
        Gtk::TreeModelColumn<Glib::ustring> m_col_name;
};

void notify(enum mpd_idle, mpd_status * status)
{
    cerr << "Cool." << endl;
}

int main(int argc, char *argv[])
{
    Gtk::Main kit(argc,argv);
    try
    {
        Glib::RefPtr<Gtk::Builder> builder = Gtk::Builder::create_from_file("ui/Freya.glade");
        Gtk::Window * main_window = NULL;
        builder->get_widget("FreyaMainWindow", main_window);

        builder->get_widget("time_slide",time_scale);
        time_scale->set_range(0.0,100.0);
        Glib::signal_timeout().connect(sigc::ptr_fun(do_time_scale_step), 1000);

        Gtk::TreeView * plugin_listview = NULL;
        builder->get_widget("plugin_view",plugin_listview);

        ModelColumns m_Columns; 
        Glib::RefPtr<Gtk::ListStore> m_refTreeModel;
            
        //Create the Tree model:
        m_refTreeModel = Gtk::ListStore::create(m_Columns);
        plugin_listview->set_model(m_refTreeModel);

        //Fill the TreeView's model
        Gtk::TreeModel::Row row = *(m_refTreeModel->append());
        row[m_Columns.m_col_name] = "Now Playing";
        row = *(m_refTreeModel->append());
        row[m_Columns.m_col_name] = "Playlist";
        row = *(m_refTreeModel->append());
        row[m_Columns.m_col_name] = "Settings";
        plugin_listview->append_column("Browser", m_Columns.m_col_name);


        Gtk::Box * main_box = NULL;
        builder->get_widget("main_box",main_box);
        PlaylistTreeView ex;
        main_box->pack_start(ex,true,true);

        Gtk::Statusbar * statusbar = NULL;
        builder->get_widget("statusbar",statusbar);
        statusbar->push("This is the Statusbar");

        MPD::Client client;
        client.get_notify()->connect(sigc::ptr_fun(notify));

        kit.run(*main_window);

    }
    catch(const Gtk::BuilderError& e)
    {
        std::cerr << "BuilderError: " << e.what() << std::endl;
    }
    catch(const Glib::FileError& e)
    {
        std::cerr << "General exception: " << e.what() << std::endl;
    }

    return EXIT_SUCCESS;
}

