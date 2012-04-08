#include "CairoSlider.hh"
#include <cairomm/context.h>

CairoSlider::CairoSlider() :
    m_volPos(INT_MAX),
    currPerc(0.0),
    isDragging(false),
    col_active_set(false),
    col_inactive_set(false),
    col_active(NULL),
    col_inactive(NULL)
{
    set_events(Gdk::BUTTON_PRESS_MASK
               | Gdk::BUTTON_RELEASE_MASK
               | Gdk::POINTER_MOTION_MASK
               | Gdk::SCROLL_MASK);
}

/////////////////////////

int CairoSlider::get_border()
{
    return m_volPos;
}

/////////////////////////

/*
 * Change the color separator accordingly
 * and calculate the percentage value of the volume
 */
void CairoSlider::recalculate(double x, int step)
{
    int width = get_allocation().get_width();
    if(step == 0)
    {
        m_volPos = CLAMP(x,0,width);
    }
    else
    {
        int next = m_volPos + step;
        m_volPos = CLAMP(next,0,width);
    }
    queue_draw();
    currPerc = (100.0 * m_volPos) / width;
    if(m_Timerguard.elapsed() > get_update_timeout())
    {
        // Gets executed once nothing importent happens
        Glib::signal_idle().connect_once(
            sigc::mem_fun(*this,&CairoSlider::on_percent_change),
            Glib::PRIORITY_LOW);
        m_Timerguard.reset();
    }
}

/////////////////////////

double CairoSlider::get_percentage()
{
    return currPerc;
}

/////////////////////////

void CairoSlider::set_percentage(double p)
{
    currPerc = CLAMP(p,0,100);
    m_volPos = (currPerc/100.0) * get_allocation().get_width();
    queue_draw();
}


/////////////////////////
//////// SIGNALS ////////
/////////////////////////

/*
 * Triggered when moving the mouse pointer while being in the widget
 * Used to 'drag' the volume slider
 */
bool CairoSlider::on_motion_notify_event(GdkEventMotion * ev)
{
    if(isDragging)
    {
        recalculate(ev->x,0);
    }
    return true;
}

/////////////////////////

/*
 * Triggered when releasing the the mousebutton,
 * used to end a 'drag' so on_motion_notify_event
 * knows when to change the volume
 */
bool CairoSlider::on_button_release_event(GdkEventButton * ev)
{
    if(ev != NULL)   // This is actually just to get rid of a warning :(
    {
        isDragging = false;
    }
    return true;
}

/////////////////////////

/*
 * Triggered when clicking into the widget
 * Calculates the clicked position and volume
 */
bool CairoSlider::on_button_press_event(GdkEventButton * ev)
{
    recalculate(ev->x,0);
    isDragging = true;
    return true;
}

/////////////////////////

/*
 * Triggered when scrolling with the mouse wheel,
 * while being in the widget,
 * used to increase the volume in steps
 */
bool CairoSlider::on_scroll_event(GdkEventScroll * ev)
{
    // There does not seem to be a Gdk::SCROLL_UP..
    recalculate(ev->x,ev->direction == GDK_SCROLL_UP ? 5 : -5);
    return true;
}

/////////////////////////

Gdk::RGBA& CairoSlider::get_active_color()
{
    if(!col_active_set)
    {
        Glib::RefPtr<Gtk::StyleContext> ctx = get_style_context();
        col_active = new Gdk::RGBA(ctx->get_background_color(Gtk::STATE_FLAG_SELECTED));
        col_active_set = true;
    }
    return *col_active;
}

/////////////////////////

Gdk::RGBA& CairoSlider::get_inactive_color()
{
    if(!col_inactive_set)
    {
        Glib::RefPtr<Gtk::StyleContext> ctx = get_style_context();
        col_inactive = new Gdk::RGBA(ctx->get_color(Gtk::STATE_FLAG_NORMAL));
        col_inactive_set = true;
    }
    return *col_inactive;
}

/////////////////////////

CairoSlider::~CairoSlider()
{
    delete col_active;
    delete col_inactive;
}

/////////////////////////
