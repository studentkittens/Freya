#include "Listener.hh"
#include "../Log/Writer.hh"

namespace MPD
{
    //--------------------------------

    Listener::Listener(EventNotifier * notifier, Connection& sync_conn) : m_NData(sync_conn)
    {
        mp_Parser = mpd_parser_new();
        async_conn = mpd_connection_get_async(sync_conn.get_connection());
        async_socket_fd = mpd_async_get_fd(async_conn); 

        idle_events = (enum mpd_idle)0;
        io_eventmask = (enum mpd_async_event)0;
        is_idle = false;

        g_assert(notifier);
        mp_Notifier = notifier;

        g_assert(sync_conn.get_connection());
        m_NData.update_all();
        
        mp_Conn = &sync_conn;
    }

    //--------------------------------

    Listener::~Listener()
    {
        if(mp_Parser!= NULL)
        {
            mpd_parser_free(mp_Parser);
        }
    }

    //--------------------------------

    bool Listener::is_idling(void)
    {
        return is_idle;
    }

    //--------------------------------
    //--------------------------------
    //--------------------------------

    bool Listener::check_async_error(void)
    {
        bool result = false;
        if(async_conn != NULL && mpd_async_get_error(async_conn) != MPD_ERROR_SUCCESS)
        {
            Warning("AsyncError: %s",mpd_async_get_error_message(async_conn));
            result = true;
        }
        return result;
    }

    //--------------------------------

    void Listener::invoke_user_callback(long overwrite_events = -1)
    {
        if(idle_events != 0)
        {
            /* Leave for callback - which is gonna be active */
            leave();

            if(overwrite_events != -1)
                idle_events = (unsigned)overwrite_events;

            /* Somethin changed.. update therefore */
            m_NData.update_all();

            /* Iterare over the enum (this is weird) */
            for(unsigned mask = 1; /* empty */; mask = mask << 1)
            {
                const char * event_name = mpd_idle_name((enum mpd_idle)mask);
                if(event_name == NULL)
                    break;

                unsigned actual_event = idle_events & mask;
                if(actual_event != 0)
                {
                    Debug("  :%s",event_name);

                    /* Notify observers */
                    mp_Notifier->emit((enum mpd_idle)actual_event,m_NData);
                }
            }

            /* Delete old events  */
            idle_events = 0;

            /* Re-enter idle mode */
            enter();
        }
    }

    //--------------------------------

    bool Listener::parse_response(char *line)
    {
        enum mpd_parser_result result;

        result = mpd_parser_feed(mp_Parser, line);
        switch (result) 
        {
            case MPD_PARSER_ERROR:

                io_eventmask = (enum mpd_async_event)0;
                check_async_error();
                Error("ParserError: %d - %s",
                        mpd_parser_get_server_error(mp_Parser),
                        mpd_parser_get_message(mp_Parser));

                return false;

            case MPD_PARSER_PAIR:

                if(g_strcmp0(mpd_parser_get_name(mp_Parser),"changed") == 0)
                {
                    const char * value = mpd_parser_get_value(mp_Parser);
                    idle_events |= mpd_idle_name_parse(value);
                }
                break;

            case MPD_PARSER_MALFORMED:

                io_eventmask = (enum mpd_async_event)0;
                check_async_error();
                return false;

            case MPD_PARSER_SUCCESS:

                io_eventmask = (enum mpd_async_event)0;
                invoke_user_callback();
                return true;

        }
        return true;
    }

    //--------------------------------

    bool Listener::recv_parseable(void)
    {
        char * line = NULL;

        while ((line = mpd_async_recv_line(async_conn)) != NULL)
        {
            if(parse_response(line) == false)
                return false;
        }

        if (mpd_async_get_error(async_conn) != MPD_ERROR_SUCCESS)
        {
            io_eventmask = (enum mpd_async_event)0;
            check_async_error();
            return false;
        }

        return true;
    }

    //--------------------------------

    void Listener::create_watch(enum mpd_async_event events)
    {
        /* Convert mpd events to glib events */
        Glib::IOCondition condition = Listener::MPDAsyncEvent_to_GIOCondition(events);

        /* Disconnect old connection */
        if(io_functor.connected())
        {
            io_functor.disconnect();
        }

        /* Add a watch for this, io_callback() gets called whenever data is available */
        io_functor = Glib::signal_io().connect(sigc::mem_fun(this,&Listener::io_callback), async_socket_fd,condition, Glib::PRIORITY_HIGH);
    }

    //--------------------------------

    gboolean Listener::io_callback(Glib::IOCondition condition)
    {
        /* Tell libmpdclient that it should do the IO now */
        if(mpd_async_io(async_conn, Listener::GIOCondition_to_MPDAsyncEvent(condition)) == false)
            return false;

        /* There is incoming data - receive them */
        if((condition & G_IO_IN) || (condition & G_IO_PRI)) 
        {
            if(recv_parseable() == false) 
            {
                Error("Could not parse response");
                return false;
            }
        }

        enum mpd_async_event events = mpd_async_events(async_conn);
        if (events == 0) 
        {
            Debug("no events -> removing watch");

            /* no events - disable watch */
            io_eventmask = (enum mpd_async_event)0;
            return false;
        }
        else if (events != io_eventmask) 
        {
            /* different event mask: make new watch */
            create_watch(events);
            io_eventmask = events;
            return false;
        }
        return true;
    }

    //--------------------------------

    bool Listener::enter(void)
    {
        if(is_idling() == false)
        {
            if(mpd_async_send_command(async_conn, "idle", NULL) == false)
            {
                check_async_error();
                return false;
            }

            /* Get a bitmask of events that needs to be watched */
            enum mpd_async_event events = mpd_async_events(async_conn);

            /* Indicate we get into idlemode */
            is_idle = true;

            /* Add a watch on the socket */
            create_watch(events);

            return true;
        }
        else
        {
            Warning("Cannot enter idling mode: Already idling.");
            return false;
        }
    }

    //--------------------------------

    void Listener::leave(void)
    {
        if(is_idling() && mp_Conn->is_connected())
        {
            if(io_functor.connected()) 
            {
                bool is_fatal = false;

                /* New game - new dices */
                io_eventmask = (enum mpd_async_event)0;

                /* Make sure no idling is running */
                if(idle_events == 0)
                {
                    mpd_run_noidle(mp_Conn->get_connection());
                }

                /* Check for errors that may happened shortly */            
                if(mpd_connection_get_error(mp_Conn->get_connection()) != MPD_ERROR_SUCCESS) 
                {
                    Error("Error while leaving idle mode: %s",mpd_connection_get_error_message(mp_Conn->get_connection()));
                    is_fatal = (mpd_connection_clear_error(mp_Conn->get_connection()) == false);
                }

                if(is_fatal == false)
                {
                    /* Indicate we left */
                    is_idle = false;

                    /* Disconnect the watchdog for now */
                    io_functor.disconnect();
                }
            }
            else Error("IOFunctor already disconnected");
        }
        else Warning("Cannot leave when already left (Dude!)");
    }

    //--------------------------------

    NotifyData& Listener::get_notify_data(void)
    {
        return m_NData;
    }

    //--------------------------------

    void Listener::force_update(void)
    {
        idle_events = (enum mpd_idle)1;
        mpd_run_noidle(mp_Conn->get_connection());
        invoke_user_callback(UINT_MAX);
    }

    //--------------------------------
    // Static methods
    //--------------------------------

    enum mpd_async_event Listener::GIOCondition_to_MPDAsyncEvent(Glib::IOCondition condition)
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

    Glib::IOCondition Listener::MPDAsyncEvent_to_GIOCondition(enum mpd_async_event events)
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

} // namespace MPD
