#ifndef FREYA_EVENTIMAGE_HH
#define FREYA_EVENTIMAGE_HH

#include <gtkmm.h>

namespace Browser
{
    class EventImage : public Gtk::EventBox
    {
        public:
            EventImage();
            EventImage(Glib::RefPtr<Gdk::Pixbuf>& pix);
            ~EventImage();

        private:
            /* Common ctor */
            void setup(Glib::RefPtr<Gdk::Pixbuf>& pix);

            /* On click callback */
            virtual bool on_button_press_event(GdkEventButton * ev);

            /* Actual Image widget */
            Gtk::Image * image;

            /* Shared store for 'noimage' */
            static Glib::RefPtr<Gdk::Pixbuf> noImagePix;
    };
            
}

#endif /* end of include guard: FREYA_EVENTIMAGE_HH */
