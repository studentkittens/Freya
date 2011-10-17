#include "IdleListener.hpp"

//--------------------------------

IdleListener::IdleListener(mpd_connection * sync_conn)
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

IdleListener::~IdleListener()
{
    if(this->parser != NULL)
    {
        mpd_parser_free(this->parser);
    }
}

//--------------------------------

mpd_connection * IdleListener::get_connection()
{
   if(this->is_idle)
   {
       this->leave();
   } 

   return this->conn;
}

//--------------------------------
//--------------------------------
//--------------------------------
//--------------------------------
//--------------------------------
//--------------------------------

bool IdleListener::check_async_error(void)
{
    bool result = false;
    if(this->async_conn != NULL && mpd_async_get_error(this->async_conn) != MPD_ERROR_SUCCESS)
    {
        g_printerr("AsyncError: %s\n",mpd_async_get_error_message(this->async_conn));
        result = true;
    }
    return result;
}

//--------------------------------

void IdleListener::invoke(void)
{
	if (this->idle_events != 0)
    {
        g_printerr("Got event: %s\n",mpd_idle_name((enum mpd_idle)this->idle_events));
        this->enter();
    }
}

//--------------------------------

bool IdleListener::parse_response(char *line)
{
	enum mpd_parser_result result;

    result = mpd_parser_feed(this->parser, line);
    switch (result) 
    {
        case MPD_PARSER_MALFORMED:

            this->io_eventmask = (enum mpd_async_event)0;
            this->check_async_error();
            return false;

        case MPD_PARSER_SUCCESS:

            this->io_eventmask = (enum mpd_async_event)0;
            this->invoke();
            return true;

        case MPD_PARSER_ERROR:

            this->io_eventmask = (enum mpd_async_event)0;
            this->check_async_error();
            g_printerr("Parser Error: %d - %s\n",
                    mpd_parser_get_server_error(this->parser),
                    mpd_parser_get_message(this->parser));

            return false;

        case MPD_PARSER_PAIR:

            if (g_strcmp0(mpd_parser_get_name(this->parser),"changed") == 0)
            {
                this->idle_events |= mpd_idle_name_parse(mpd_parser_get_value(this->parser));
            }
            break;
    }
    return true;
}

//--------------------------------

bool IdleListener::recv_parseable(void)
{
    char * line = NULL;

    while ((line = mpd_async_recv_line(this->async_conn)) != NULL)
    {
        if(this->parse_response(line) == false)
           return false;
    }

    if (mpd_async_get_error(this->async_conn) != MPD_ERROR_SUCCESS)
    {
        cerr << "Cannot parse :-(" << endl;
        this->io_eventmask = (enum mpd_async_event)0;
        check_async_error();
        return false;
    }

    return true;
}

//--------------------------------

void IdleListener::create_watch(enum mpd_async_event events)
{
    /* Convert mpd events to glib events */
    Glib::IOCondition condition = IdleListener::MPDAsyncEvent_to_GIOCondition(events);
   
    /* Disconnect old connection */
    if(io_functor.connected())
    {
        io_functor.disconnect();
    }

    /* Add a watch for this, io_callback() gets called whenever data is available */
    this->io_functor = Glib::signal_io().connect(sigc::mem_fun(this,&IdleListener::io_callback), this->async_socket_fd,condition);
}

//--------------------------------

gboolean IdleListener::io_callback(Glib::IOCondition condition)
{
    /* Tell libmpdclient that it should do the IO now */
    if(mpd_async_io(async_conn, IdleListener::GIOCondition_to_MPDAsyncEvent(condition)) == false)
        return false;

    /* There is incoming data - receive them */
    if((condition & G_IO_IN) != 0) 
    {
        if(this->recv_parseable() == false) 
        {
            cerr << "Cannot parse?" << endl;
            return false;
        }
    }

    enum mpd_async_event events = mpd_async_events(this->async_conn);
    if (events == 0) 
    {
        cerr << "no events -> removing watch" << endl;
        /* no events - disable watch */
        this->io_eventmask = (enum mpd_async_event)0;
        return false;
    }
    else if (events != this->io_eventmask) 
    {
        cerr << "different mask -> removing watch and adding new" << endl;

        /* different event mask: make new watch */
        this->create_watch(events);
        this->io_eventmask = events;
        return false;
    }
    cerr << "Keeping watch" << endl;
    return true;
}

//--------------------------------

bool IdleListener::enter(void)
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

//--------------------------------

void IdleListener::leave(void)
{
    this->io_functor.disconnect();
	this->io_eventmask = (enum mpd_async_event)0;

    /* Any new events? */
	enum mpd_idle new_idle_events = 
        (this->idle_events == 0)
		? mpd_run_noidle(this->conn)
		: mpd_recv_idle(this->conn, false);

	if (new_idle_events == 0 && mpd_connection_get_error(this->conn) != MPD_ERROR_SUCCESS) 
    {
		g_printerr("Error while leaving idle mode: %s\n",mpd_connection_get_error_message(this->conn));
	}
    else
    {
        /* Indicate we left */
        this->is_idle = false;

        /* Mix in new events */
        this->idle_events |= new_idle_events;

        /* Announce them */
        this->invoke();
    }
}

//--------------------------------