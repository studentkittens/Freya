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

    void set(Glib::RefPtr<Gdk::Pixbuf>& pix);
    void set(const char * data, gsize len, int width = 200, int height = 200, bool aspect = false);
    void set_default();

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
