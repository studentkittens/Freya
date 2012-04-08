#ifndef GTKMM_EXAMPLE_CAIROSLIDER_H
#define GTKMM_EXAMPLE_CAIROSLIDER_H

#include <gtkmm/eventbox.h>
#include <gtkmm/drawingarea.h>

class CairoSlider : public Gtk::DrawingArea
{
public:
    CairoSlider();
    ~CairoSlider();

protected:

    /**
     * @brief Override to draw the widget
     *
     * on_draw() is always called when the widget needs to be redrawn,
     * therefore all drawing logic should happen here, possibly in
     * a optimized way.
     *
     * See also: http://developer.gnome.org/gtkmm-tutorial/3.0/chapter-drawingarea.html
     *
     * @param cr a Cairo::Context
     *
     * @return true if everything is handeled, false to let other callbacks be called
     */
    virtual bool on_draw(const Cairo::RefPtr<Cairo::Context>& cr) = 0;

    /**
     * @brief Returns the current position of the slider
     *
     * This is useful in on_draw(), you shouldn't calculate the
     * percentage value from this though
     *
     * @return integer between 0 and allocation.get_width()
     */
    int get_border();

    /**
     * @brief Get the current percentage shown in the slider
     *
     * @return a double from 0.0 to 100.0
     */
    double get_percentage();

    /**
     * @brief Set the slider to p and redraw
     *
     * @param p a double between 0.0 and 100.0
     */
    void set_percentage(double p);

    /**
     * @brief Called whenever the percentage changes
     */
    virtual void on_percent_change() = 0;

    /**
     * @brief Only allows updates every <x.xx> seconds
     */
    virtual double get_update_timeout()
    {
        return 0.05;
    }

    /**
     * @brief Get the active color of the slider
     *
     * @return a non-null Gdk::RGBA instance
     */
    virtual Gdk::RGBA& get_active_color();
    /**
     * @brief Get the inactive color of the slider
     *
     * @return a non-null Gdk::RGBA instance
     */
    virtual Gdk::RGBA& get_inactive_color();

private:

    // Signals:

    // These signals should not be overwritten, therefore private
    bool on_button_press_event(GdkEventButton * ev);
    bool on_scroll_event(GdkEventScroll * ev);
    bool on_motion_notify_event(GdkEventMotion * ev);
    bool on_button_release_event(GdkEventButton * ev);

    // Vars:

    // Position frome where black lines are drawn
    int m_volPos;

    // Current percentage
    double currPerc;

    // Calculate the input
    void recalculate(double x, int step);

    // true when 'dragging' with the mousepointer
    bool isDragging;

    // A timer to prevent 'oversetting' percentage
    Glib::Timer m_Timerguard;

    bool col_active_set, col_inactive_set;
    Gdk::RGBA * col_active;
    Gdk::RGBA * col_inactive;
};

#endif // GTKMM_EXAMPLE_CAIROSLIDER_H
