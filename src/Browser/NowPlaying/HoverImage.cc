#include "HoverImage.hh"
#include "../../Utils/Utils.hh"

namespace Browser 
{
    /*
     * CTor for a Glade derived image
     * (== the cover image for now), 
     * it has to be embedded inside a Eventbox.
     */
    HoverImage::HoverImage(BaseObjectType* cobject, const Glib::RefPtr<Gtk::Builder>& builder)
        : Gtk::EventBox(cobject)
    {
        BUILDER_GET(builder,"np_Image",mImg);
        setup();
    }

    //////////////////////////////

    /*
     * A standard constructor so also non-glade images
     * can use it too (EventBox has an empty ctor so not listed)
     */
    HoverImage::HoverImage()
    {
       mImg = Gtk::manage(new Gtk::Image());
       if(mImg != NULL) {
         add(*mImg);
         setup();
       }
    }
    
    //////////////////////////////
   
    /*
     * Common setup
     */ 
    void HoverImage::setup()
    {
        const char * path = "ui/gfx/nocover.png";
        mNoImage = Gdk::Pixbuf::create_from_file(path);
        if(!mNoImage) {
            Warning("Cannot load nocover.png from %s",path);
        }

        mImg->set(mNoImage);
        this->signal_button_press_event().connect(sigc::mem_fun(
                    *this,&HoverImage::on_image_clicked));
    }
    
    //////////////////////////////
          
    /*
     * Triggered when user clicks on the surrounding eventbox,
     * pops up a Window with original size of the image
     */ 
    bool HoverImage::on_image_clicked(GdkEventButton * ev)
    {
        puts("Clicked.");
        Gtk::Window win(Gtk::WINDOW_TOPLEVEL);
        Gtk::Image fullSizeImg(mNoImage);
        win.add(fullSizeImg);
        win.show_all();
        return true;
    }
}
