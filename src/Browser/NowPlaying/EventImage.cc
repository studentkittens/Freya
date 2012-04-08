#include "EventImage.hh"
#include "../../Log/Writer.hh"
#include "../../Utils/Utils.hh"
#include "../../GManager/Window.hh"
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
                EventImage::noImagePix = Utils::pixbuf_internal_fetch(NO_IMAGE_PATH);
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

    /* 
     * Plain old C Callback,
     * since it is an implementation detail
     */
    bool on_popup_focus_out(GdkEventFocus *event, Gtk::Window * pWindow, Gtk::Image * pImage)
    {
        delete pWindow;
        delete pImage;
        return true;
    }
    
    /////////////////

    bool EventImage::on_button_press_event(GdkEventButton * ev)
    {
        if(image != NULL) {

            /*
             * Configure a new popup window
             */
            Gtk::Window * pWindow = new Gtk::Window(Gtk::WINDOW_TOPLEVEL);
            pWindow->set_title("Cover View");
            pWindow->set_border_width(5);
            pWindow->set_resizable(false);
            pWindow->set_decorated(false);
            pWindow->set_skip_taskbar_hint(true);
            pWindow->set_skip_pager_hint(true);
            pWindow->set_position(Gtk::WIN_POS_MOUSE);
            pWindow->set_events(Gdk::FOCUS_CHANGE_MASK);

            /*
             * Say that the popup belongs
             * to the mainwindow
             */
            Gtk::Window * pMainWindow = GManager::Window::get_current_window();
            if(pMainWindow) {
                pWindow->set_transient_for(*pMainWindow);
            }

            /*
             * Blackify borders
             */
            Gdk::RGBA black;
            black.set_rgba(0,0,0);
            pWindow->override_background_color(black); 

            /*
             * TODO: Add way to get the original pixbuf
             */
            Glib::RefPtr<Gdk::Pixbuf> img_buf = image->get_pixbuf();
            img_buf = img_buf->scale_simple(390,390,Gdk::INTERP_BILINEAR);
            Gtk::Image * pImage = new Gtk::Image(img_buf);

            pWindow->add(*pImage);
            //pWindow->set_size_request(img_buf->get_width() + 10, img_buf->get_height() + 10);
            pWindow->set_size_request(400,400);

            /*
             * Close window once window moves out of focus,
             * i.e. the mouse leaves the window,
             *
             * also bind window and image to free them
             */
            pWindow->signal_focus_out_event().connect(
                    sigc::bind(sigc::ptr_fun(on_popup_focus_out),pWindow,pImage)
                    );

            pWindow->show_all();
            pWindow->grab_focus();
        }
        return true;
    }
}
