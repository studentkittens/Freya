#include "FreyaWindow.hh"

FreyaWindow::FreyaWindow(const Glib::RefPtr<Gtk::Builder> &builder)
{
   main_window=NULL;
   BUILDER_GET_NO_MANAGE(builder,"FreyaMainWindow",main_window);

   main_window->signal_delete_event().connect(sigc::mem_fun(*this,&FreyaWindow::on_delete_event));

}

FreyaWindow::~FreyaWindow()
{
    if(main_window!=NULL)
    {
        delete main_window;
        main_window=NULL;
    }
}


bool FreyaWindow::on_delete_event(GdkEventAny* event)
{
    if(CONFIG_GET_AS_INT("settings.trayicon.totrayonclose"))
    {
        main_window->hide();
    }
    else
    {
        Gtk::Main::quit();
    }
    return true;
}

Gtk::Window* FreyaWindow::get_window(void)
{
    return this->main_window;
}
