#include "ImageWall.hh"
#include "EventImage.hh"
#include "../../Glyr/Request.hh"

namespace Browser 
{

/////////////////

ImageWall::ImageWall(int xmax, int ymax)
    : col(0), row(0)
{
    this->xmax = MAX(xmax,1);
    this->ymax = MAX(ymax,1);
}

/////////////////

void ImageWall::add(std::string& path)
{
    Glib::RefPtr<Gdk::Pixbuf> pb = Gdk::Pixbuf::create_from_file(path,80,80,false);
    EventImage * img = Gtk::manage(new EventImage(pb));
    if(img != NULL) {
        add(*img);
    }
}

/////////////////

void ImageWall::add(Gtk::Widget& w)
{
    attach(w, row++ , col ,1,1);
    if(col / xmax != 0 || row % ymax == 0) {
        col++;
        row = 0;
    }
    show_all();
}

/////////////////

void ImageWall::add(GlyrMemCache * c, int width, int height, bool aspect)
{
    Glib::RefPtr<Gdk::Pixbuf> pix = Glyr::create_pixbuf_from_cache(c,width,height,aspect);
    EventImage * img = Gtk::manage(new EventImage(pix));
    if(img != NULL) {
        add(*img);
    }
}

/////////////////

void ImageWall::clear()
{
    col = 0;
    row = 0;

    typedef std::vector<Widget*> Widgets;
    Widgets list =  Gtk::Container::get_children();
    for(Widgets::iterator  it = list.begin(); it != list.end(); it++)
    {
        Gtk::Widget * w = *it;
        if(w != NULL) {
            Gtk::Container::remove(*w);
            delete  w;
        }
    }
}

/////////////////
}
