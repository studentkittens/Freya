#include "Listener.hh"
#include "../LogHandler/LogHandler.hh"

namespace MPD
{
    //--------------------------------

    Listener::Listener(mpd_connection * sync_conn)
    {
        if(sync_conn != NULL)
        {
            this->conn = sync_conn;
            this->parser = mpd_parser_new();
            this->async_conn = mpd_connection_get_async(sync_conn);
            this->async_socket_fd = mpd_async_get_fd(this->async_conn); 
            this->idle_events = (enum mpd_idle)0;
            this->io_eventmask = (enum mpd_async_event)0;
            this->is_idle = false;
        }
    }

    //--------------------------------

    Listener::~Listener()
    {
        if(this->parser != NULL)
        {
            mpd_parser_free(this->parser);
        }
    }

    //--------------------------------

    bool Listener::is_idling(void)
    {
        return this->is_idle;
    }

    //--------------------------------
    //--------------------------------
    //--------------------------------
    //--------------------------------

    bool Listener::check_async_error(void)
    {
        bool result = false;
        if(this->async_conn != NULL && mpd_async_get_error(this->async_conn) != MPD_ERROR_SUCCESS)
        {
            Warning("AsyncError: %s",mpd_async_get_error_message(this->async_conn));
            result = true;
        }
        return result;
    }

    //--------------------------------

    void Listener::invoke_user_callback(void)
    {
        if (this->idle_events != 0)
        {
            /* Leave for callback - which is gonna be active */
            this->leave();

            /* Iterare over the enum */
            for(unsigned mask = 1; /* None */; mask = mask << 1)
            {
                const char * event_name = mpd_idle_name((enum mpd_idle)mask);
                if(event_name == NULL)
                    break;

                if(this->idle_events & mask)
                {
                    Info("  :%s",event_name);
                    //  <-- Call callback here --> //
                }
            }


            /* Delete old events  */
            this->idle_events = 0;

            /* Re-enter idle mode */
            this->enter();
        }
    }

    //--------------------------------

    bool Listener::parse_response(char *line)
    {
        enum mpd_parser_result result;

        result = mpd_parser_feed(this->parser, line);
        switch (result) 
        {
            case MPD_PARSER_ERROR:

                this->io_eventmask = (enum mpd_async_event)0;
                this->check_async_error();
                Error("Parser Error: %d - %s",
                        mpd_parser_get_server_error(this->parser),
                        mpd_parser_get_message(this->parser));

                return false;

            case MPD_PARSER_PAIR:

                if (g_strcmp0(mpd_parser_get_name(this->parser),"changed") == 0)
                {
                    const char * value = mpd_parser_get_value(this->parser);
                    this->idle_events |= mpd_idle_name_parse(value);
                }
                break;

            case MPD_PARSER_MALFORMED:

                this->io_eventmask = (enum mpd_async_event)0;
                this->check_async_error();
                return false;

            case MPD_PARSER_SUCCESS:

                this->io_eventmask = (enum mpd_async_event)0;
                this->invoke_user_callback();
                return true;

        }
        return true;
    }

    //--------------------------------

    bool Listener::recv_parseable(void)
    {
        char * line = NULL;

        while ((line = mpd_async_recv_line(this->async_conn)) != NULL)
        {
            if(this->parse_response(line) == false)
                return false;
        }

        if (mpd_async_get_error(this->async_conn) != MPD_ERROR_SUCCESS)
        {
            this->io_eventmask = (enum mpd_async_event)0;
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
        this->io_functor = Glib::signal_io().connect(sigc::mem_fun(this,&Listener::io_callback), this->async_socket_fd,condition, Glib::PRIORITY_HIGH);
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
            if(this->recv_parseable() == false) 
            {
                Error("Could not parse response");
                return false;
            }
        }

        enum mpd_async_event events = mpd_async_events(this->async_conn);
        if (events == 0) 
        {
            Debug("no events -> removing watch");

            /* no events - disable watch */
            this->io_eventmask = (enum mpd_async_event)0;
            return false;
        }
        else if (events != this->io_eventmask) 
        {
            /* different event mask: make new watch */
            this->create_watch(events);
            this->io_eventmask = events;
            return false;
        }
        return true;
    }

    //--------------------------------

    bool Listener::enter(void)
    {
        if(this->is_idling() == false)
        {
            if(mpd_async_send_command(this->async_conn, "idle", NULL) == false)
            {
                check_async_error();
                return false;
            }

            /* Get a bitmask of events that needs to be watched */
            enum mpd_async_event events = mpd_async_events(this->async_conn);

            /* Indicate we get into idlemode */
            this->is_idle = true;

            /* Add a watch on the socket */
            this->create_watch(events);

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
        if(this->is_idling() == true)
        {
            if(this->io_functor.connected())    
            {
                bool is_fatal = false;
                enum mpd_idle new_idle_events = (enum mpd_idle)0;

                /* New game - new dices */
                this->io_eventmask = (enum mpd_async_event)0;

                /* Make sure no idling is running */
                if(this->idle_events == 0)
                    new_idle_events = mpd_run_noidle(this->conn);

                /* Check for errors that may happened shortly */            
                if (new_idle_events == 0 && mpd_connection_get_error(this->conn) != MPD_ERROR_SUCCESS) 
                {
                    Error("Error while leaving idle mode: %s",mpd_connection_get_error_message(this->conn));
                    is_fatal = (mpd_connection_clear_error(this->conn) == false);
                }

                if(is_fatal == false)
                {
                    /* Indicate we left */
                    this->is_idle = false;

                    /* Mix in new events */
                    // TODO: Does this even make sense?
                    //this->idle_events |= new_idle_events;
                    //this->invoke_user_callback();

                    /* Disconnect the watchdog for now */
                    this->io_functor.disconnect();
                }
            }
            else Error("IOFunctor already disconnected");
        }
        else Warning("Cannot leave when already left (Dude!)");

    }

    //--------------------------------
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
