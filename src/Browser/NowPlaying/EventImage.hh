#ifndef FREYA_EVENTIMAGE_HH
#define FREYA_EVENTIMAGE_HH

#include <gtkmm.h>

namespace Browser
{
    class EventImage : public Gtk::EventBox
    {
        public:
            EventImage(Glib::RefPtr<Gdk::Pixbuf> pix);

        private:
            virtual bool on_button_press_event(GdkEventButton * ev);
            Gtk::Image image;
    };
}

#endif /* end of include guard: FREYA_EVENTIMAGE_HH */
