#ifndef FREYA_IDLELISTENER_GUARD
#define FREYA_IDLELISTENER_GUARD

#include "includes.hpp"

class IdleListener
{
    public:
    IdleListener(mpd_connection * sync_conn);
    ~IdleListener();

    /* Enter idle mode
     * Returns: true on success 
     */
    bool enter(void);

    /* Leave idle mode (in order to send commands)
     */
    void leave(void);

    /* Checks if connection is in idle mode
     */
    bool is_idling(void);

    //---------------//
    // Classmembers  //
    //---------------//
    
    /**
     * Utility (therefore static) function to
     * convert a GIOCondition bit mask to #mpd_async_event.
     */
    static enum mpd_async_event GIOCondition_to_MPDAsyncEvent(Glib::IOCondition condition)
    {
        int events = 0;

        if (condition & G_IO_IN)
            events |= MPD_ASYNC_EVENT_READ;

        if (condition & G_IO_OUT)
            events |= MPD_ASYNC_EVENT_WRITE;

        if (condition & G_IO_HUP)
            events |= MPD_ASYNC_EVENT_HUP;

        if (condition & G_IO_ERR)
            events |= MPD_ASYNC_EVENT_ERROR;

        return (enum mpd_async_event)events;
    }

    //--------------------------------

    /**
     * Converts a #mpd_async_event bit mask to GIOCondition.
     */
    static Glib::IOCondition MPDAsyncEvent_to_GIOCondition(enum mpd_async_event events)
    {
        int condition = 0;

        if (events & MPD_ASYNC_EVENT_READ)
            condition |= G_IO_IN;

        if (events & MPD_ASYNC_EVENT_WRITE)
            condition |= G_IO_OUT;

        if (events & MPD_ASYNC_EVENT_HUP)
            condition |= G_IO_HUP;

        if (events & MPD_ASYNC_EVENT_ERROR)
            condition |= G_IO_ERR;

        return (Glib::IOCondition)condition;
    }

    private:

    /* check if async connection is doing weird things */
    bool check_async_error(void);
    bool recv_parseable(void);
    gboolean io_callback(Glib::IOCondition condition);
    bool parse_response(char *line);
    void invoke_user_callback(void);
    void create_watch(enum mpd_async_event events);

    //-----------------//
    // Instancemembers //
    //-----------------//

    /* Synchronous connection from MPDClient */
    mpd_connection * conn;

    /* true if in idlemode */
    bool is_idle;

    /* A reponse parser */
    struct mpd_parser * parser;

    /* Non blocking connection */
    struct mpd_async  * async_conn;

    /* The fd id of async_conn */
    int async_socket_fd;

    /* What IO events did happen? */
    enum mpd_async_event io_eventmask;

    /**/
    int idle_events;

    /* A functor representing the io_callback */
    sigc::connection io_functor;
 };

#endif
