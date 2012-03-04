#include "EventImage.hh"

namespace Browser 
{
    /////////////////

    EventImage::EventImage(Glib::RefPtr<Gdk::Pixbuf> pix)
        : image(pix) 
    {
        add(image);
        set_border_width(1);
    }

    /////////////////

    bool EventImage::on_button_press_event(GdkEventButton * ev)
    {
        Gtk::Dialog win;
        Gtk::Image img(image.get_pixbuf());
        win.get_content_area()->add(img);
        win.show_all();
        win.run();
        return true;
    }
}
