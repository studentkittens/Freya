 /***********************************************************
* This file is part of Freya 
* - A free MPD Gtk3 MPD Client -
* 
* Authors: Christopher Pahl, Christoph Piechula,
*          Eduard Schneider, Marc Tigges
*
* Copyright (C) [2011-2012]
* Hosted at: https://github.com/studentkittens/Freya
*
*              __..--''``---....___   _..._    __
*    /// //_.-'    .-/";  `        ``<._  ``.''_ `. / // /
*   ///_.-' _..--.'_                        `( ) ) // //
*   / (_..-' // (< _     ;_..__               ; `' / ///
*    / // // //  `-._,_)' // / ``--...____..-' /// / //  
*  Ascii-Art by Felix Lee <flee@cse.psu.edu>
*
* Freya is free software: you can redistribute it and/or modify
* it under the terms of the GNU General Public License as published by
* the Free Software Foundation, either version 3 of the License, or
* (at your option) any later version.
*
* Freya is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
* GNU General Public License for more details.
*
* You should have received a copy of the GNU General Public License
* along with Freya. If not, see <http://www.gnu.org/licenses/>.
**************************************************************/
#include "Listener.hh"
#include "../Log/Writer.hh"

namespace MPD
{
    /* Typdefs for the lazy */
    typedef struct mpd_connection mpd_connection;
    typedef struct mpd_status mpd_status;
    typedef struct mpd_entity mpd_entity;

    /* Map appropiate Glib::IO events to MPD Async events,
     * and other way round. 
     */
    static const int map_IOCondtion_MPDASync[][2] = 
    {
        {G_IO_IN,  MPD_ASYNC_EVENT_READ},
        {G_IO_OUT, MPD_ASYNC_EVENT_WRITE},
        {G_IO_HUP, MPD_ASYNC_EVENT_HUP},
        {G_IO_ERR, MPD_ASYNC_EVENT_ERROR}
    };


    /* Number of rows in above table */
    static const unsigned map_IOAsync_size = (sizeof(map_IOCondtion_MPDASync)/sizeof(unsigned));

    //--------------------------------

    Listener::Listener(EventNotifier * notifier, Connection& sync_conn) : m_NData(sync_conn)
    {

        /* No idle events, nor io events on startup,
         * call force_update() if you want to init 
         * your registered classes */
        idle_events  = 0;
        io_eventmask = (mpd_async_event)0;

        /* No idling  -> client has to call enter() itself
         * No leaving -> see above
         * No forced  -> forced is called once all observers are built
         * No working -> Callback will be called first (mostly) by force_update()
         */
        is_idle = false;
        is_leaving = false;
        is_forced = false;
        is_working = false;

        /* Save a pointer to sigc::signal */
        g_assert(notifier);
        mp_Notifier = notifier;

        /* Always make sure we have a valid status etc. */
        g_assert(sync_conn.get_connection());
        m_NData.update_all();

        /* Save a pointer so we can send sync commands
         * like "noidle" */ 
        mp_Conn = &sync_conn;

        /* Parser is used to parse the incoming events:
         * changed: player
         * changed: mixer
         * ...
         * and to convert them to appropiate enum values
         */
        mp_Parser = mpd_parser_new();

        /* We need a non-blocking connection. */
        async_conn = mpd_connection_get_async(sync_conn.get_connection());
        async_socket_fd = mpd_async_get_fd(async_conn); 
    }

    //--------------------------------

    Listener::~Listener()
    {
        leave();

        if(mp_Parser!= NULL)
            mpd_parser_free(mp_Parser);
    }

    //--------------------------------

    bool Listener::is_idling(void)
    {
        return is_idle;
    }

    //--------------------------------
    //--------------------------------
    //--------------------------------

    /* Check if a error occured */
    bool Listener::check_async_error(void)
    {
        g_assert(async_conn);

        bool result = false;
        if(mpd_async_get_error(async_conn) != MPD_ERROR_SUCCESS)
        {
            io_eventmask = (mpd_async_event)0;
            Warning("AsyncError: %s",mpd_async_get_error_message(async_conn));
            result = true;
        }
        return result;
    }

    //--------------------------------

    void Listener::invoke_user_callback(void)
    {
        if(idle_events != 0 || is_forced)
        {
            /* Leave for callback - which is gonna be active */
            leave();

            /* Do not allow to call enter() in this period */
            is_working = true;

            if(is_forced)
            {
                /* Trigger all events (0xFFFFFF) */
                idle_events = UINT_MAX; 
            }

            m_NData.update_all();

            /* Iterare over the enum (this is weird) */
            for(unsigned mask = 1; /* empty */; mask <<= 1)
            {
                const char * event_name = mpd_idle_name((mpd_idle)mask);

                /* We assume the end of the 'enum' here */
                if(event_name == NULL)
                    break;

                unsigned actual_event = (idle_events & mask);
                if(actual_event != 0)
                {
                    //Debug("  :%s",event_name);

                    /* Notify observers */
                    mp_Notifier->emit((mpd_idle)actual_event,m_NData);
                }
            }

            /* Delete old events */
            idle_events = 0;

            /* Callback finished, needs 
             * to be set to false to re-enter
             */
            is_working = false;

            /* Re-enter idle mode */
            enter();
        }
    }

    //--------------------------------

    bool Listener::parse_response(char *line)
    {
        mpd_parser_result result;
        result = mpd_parser_feed(mp_Parser, line);

        switch (result) 
        {
            case MPD_PARSER_ERROR:

                io_eventmask = (mpd_async_event)0;
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

                io_eventmask = (mpd_async_event)0;
                check_async_error();
                return false;

            case MPD_PARSER_SUCCESS:

                io_eventmask = (mpd_async_event)0;
                invoke_user_callback();
                return true;

        }
        return true;
    }

    //--------------------------------

    bool Listener::recv_parseable(void)
    {
        char * line = NULL;
        bool retval = true;

        while ((line = mpd_async_recv_line(async_conn)) != NULL)
        {
            if(parse_response(line) == false)
            {
                retval = false;
                break;
            }
        }

        check_async_error();
        return retval;
    }

    //--------------------------------

    /* Create the watchdog on the socket */
    void Listener::create_watch(mpd_async_event events)
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

    /* Called once data comes into the socket */
    gboolean Listener::io_callback(Glib::IOCondition condition)
    {
        check_async_error();
        mpd_async_event actual_event = GIOCondition_to_MPDAsyncEvent(condition);

        /* Tell libmpdclient that it should do the IO now */
        if(mpd_async_io(async_conn, actual_event) == false)
        {
            check_async_error();
            return false;
        }

        /* There is incoming data - receive them */
        if(condition & G_IO_IN) 
        {
            if(recv_parseable() == false) 
            {
                Error("Could not parse response.");
                return false;
            }
        }

        /* Returning false disconnects watchdog */
        mpd_async_event events = mpd_async_events(async_conn);
        if(events == 0) 
        {
            Debug("no events -> removing watch");

            /* no events - disable watch */
            io_eventmask = (mpd_async_event)0;
            return false;
        }
        else if(events != io_eventmask) 
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
            if(is_leaving || is_working)
                return false;

            if(mpd_async_send_command(async_conn, "idle", NULL) == false)
            {
                check_async_error();
                return false;
            }

            /* Get a bitmask of events that needs to be watched */
            mpd_async_event events = mpd_async_events(async_conn);

            /* Indicate we get into idlemode */
            is_idle = true;

            /* Add a watch on the socket */
            create_watch(events);

            return true;
        }
        else
        {
            Debug("Cannot enter idling mode: Already idling.");
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
                is_idle = false;

                /* New game - new dices */
                io_eventmask = (mpd_async_event)0;

                mpd_idle events;

                /* Make sure no idling is running */
                if(idle_events == 0)
                {
                    events = mpd_run_noidle(mp_Conn->get_connection());
                }

                is_leaving = true;

                /* Check for errors that may happened shortly */            
                mpd_error err = mpd_connection_get_error(mp_Conn->get_connection());
                if(err != MPD_ERROR_SUCCESS)
                {
                        Warning("Error#%d while leaving idle mode: %s",err,
                                mpd_connection_get_error_message(mp_Conn->get_connection()));
                }
                is_fatal = mp_Conn->clear_error();

                if(is_fatal == false)
                {
                    idle_events |= events;
                    invoke_user_callback();

                    /* Disconnect the watchdog for now */
                    io_functor.disconnect();
                }

                is_leaving = false;
            }
        }
    }

    //--------------------------------

    NotifyData& Listener::signal_client_update_data(void)
    {
        return m_NData;
    }

    //--------------------------------

    void Listener::force_update(void)
    {
        idle_events = (mpd_idle)1;
        if(is_idling())
        {
            mpd_run_noidle(mp_Conn->get_connection());
        }

        /* Inform watchers about events */
        is_forced = true;
        invoke_user_callback();
        is_forced = false;
    }

    //--------------------------------
    //--------------------------------

    mpd_async_event Listener::GIOCondition_to_MPDAsyncEvent(Glib::IOCondition condition)
    {
        int events = 0;
        for(unsigned i = 0; i < map_IOAsync_size; i++)
            if(condition & map_IOCondtion_MPDASync[i][0])
                events |= map_IOCondtion_MPDASync[i][1];

        return (mpd_async_event)events;
    }

    //--------------------------------

    /* Convert MPD's Async event to Glib's IO Socket events by a table */
    Glib::IOCondition Listener::MPDAsyncEvent_to_GIOCondition(mpd_async_event events)
    {
        /* "Mix in" by using binary OR */
        int condition = 0;
        for(unsigned i = 0; i < map_IOAsync_size; i++)
            if(events & map_IOCondtion_MPDASync[i][1])
                condition |= map_IOCondtion_MPDASync[i][0];

        return (Glib::IOCondition)condition;
    }

} // namespace MPD
