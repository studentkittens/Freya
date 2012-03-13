#include "EventImage.hh"
#include "../../Log/Writer.hh"
#include <giomm/memoryinputstream.h>

#define NO_IMAGE_PATH "ui/gfx/noimage.png"

namespace Browser 
{
    /////////////////
    
    /* Allocate actual space by declaring it here */
    Glib::RefPtr<Gdk::Pixbuf> EventImage::noImagePix;
    
    /////////////////

    EventImage::EventImage()
    {
        try {
            if(!EventImage::noImagePix) {
                EventImage::noImagePix = Gdk::Pixbuf::create_from_file(NO_IMAGE_PATH);
            }

            image = new Gtk::Image(EventImage::noImagePix);
            setup(noImagePix);

        } catch(...) {
            Warning("Can not load '%s'",NO_IMAGE_PATH);
        }
    }
    
    /////////////////

    void EventImage::set(const char * data, gsize len, int width, int height, bool aspect)
    {
        Glib::RefPtr<Gio::MemoryInputStream> is = Gio::MemoryInputStream::create();
        is->add_data(data,len);
        Glib::RefPtr<Gdk::Pixbuf> pix = Gdk::Pixbuf::create_from_stream_at_scale(is,width,height,aspect);
        set(pix);
    }

    /////////////////

    void EventImage::set(Glib::RefPtr<Gdk::Pixbuf>& pix)
    {
        image->set(pix);
    }

    /////////////////

    EventImage::EventImage(Glib::RefPtr<Gdk::Pixbuf>& pix)
    {
        setup(pix);
    }

    /////////////////
    
    void EventImage::set_default()
    {
        set(EventImage::noImagePix);
    }
    
    /////////////////

    void EventImage::setup(Glib::RefPtr<Gdk::Pixbuf>& pix)
    {
        if((image = new Gtk::Image(pix)) != NULL) {
            add(*image);
            set_border_width(1);
        }
    }

    /////////////////

    EventImage::~EventImage()
    {
        delete image;
    }

    /////////////////

    bool EventImage::on_button_press_event(GdkEventButton * ev)
    {
        if(image != NULL) {
            Gtk::Dialog win;
            Gtk::Image img(image->get_pixbuf());
            win.get_content_area()->add(img);
            win.show_all();
            win.run();
        }
        return true;
    }
}
