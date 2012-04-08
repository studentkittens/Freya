#ifndef FREYA_NP_UPDATEINTERFACE_HH
#define FREYA_NP_UPDATEINTERFACE_HH

#include "../MPD/Client.hh"
#include <glyr/glyr.h>

namespace Glyr
{
class Stack;

/**
 * @brief Very similar to AbstractClientUser, but doesnt take a Client instance
 */
class UpdateInterface
{
    friend class Glyr::Stack;

public:

    UpdateInterface() :
        requestCounter(0),
        queueCounter(0)
    {}

    /**
     * @brief This is a convienience implementationrule
     *
     * Many Metadatamanagers are implemented as Gtk::Builder derivates,
     * i.e. deriving from a widget, and letting Gtk::Builder set the basic
     * attributes. Since this requries a special ctor, those cannot implement
     * AbstractClientUser like other classes.
     *
     * @param client
     * @param event
     * @param data
     */
    virtual void update(MPD::Client& client, mpd_idle event, MPD::NotifyData& data) = 0;

    /**
     * @brief Called once an item is ready
     *
     * Note: it's only called for the last request,
     *       or when requets are enqueue()'d
     *
     * @param c the ready to use item
     */
    virtual void on_deliver(GlyrMemCache * c) {}

private:

    /**
     * @brief Counts the calls to Glyr::Stack::request()
     */
    volatile int requestCounter;
    /**
     * @brief Counts the calls to Glyr::Stack::enqueue()
     */
    volatile int queueCounter;

    /**
     * @brief This is called before each delievery
     *
     * All stuff that needs to happen on the mainloopthread
     * needs to happen here
     *
     * @param c the passed cache
     * @param disp the dispatcher that was leading to this
     * @param deliver do really deliver, or just free stuff?
     */
    void deliver_internal(GlyrMemCache * c, Glib::Dispatcher * disp, bool deliver)
    {
        if(deliver)
        {
            on_deliver(c);
        }
        delete disp;
    }
};
}

#endif /* end of include guard: FREYA_NP_UPDATEINTERFACE_HH */
