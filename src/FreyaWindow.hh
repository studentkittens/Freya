#ifndef FREYA_MAIN_WINDOW_GUARD
#define FREYA_MAIN_WINDOW_GUARD

#include <gtkmm.h>
#include "Log/Writer.hh"
#include "Utils/Utils.hh"
#include "Config/Handler.hh"

class FreyaWindow 
{
    public:
        FreyaWindow(const Glib::RefPtr<Gtk::Builder> &builder);
        ~FreyaWindow();
        Gtk::Window* get_window(void);
    protected:
        bool on_delete_event(GdkEventAny* event);
    private:
        Gtk::Window * main_window;
};

#endif
