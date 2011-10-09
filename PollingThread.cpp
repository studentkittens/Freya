#include "PollingThread.hpp"

#include <glib.h>
#include <mpd/async.h>

//--------------------------

PollingThread::PollingThread(struct mpd_connection * mpd_con)
{
    this->mpd_con    = mpd_con;
    this->old_status = NULL;
    this->finished   = false;

    // Start polling
    this->polling_thread = Glib::Thread::create(sigc::mem_fun(this, &PollingThread::poll), true);
}

//--------------------------

PollingThread::~PollingThread()
{
    if(this->old_status != NULL)
    {
        mpd_status_free(old_status);
    }
}

//--------------------------

void PollingThread::finish()
{
    int * atom = (int*)&(this->finished);
    g_atomic_int_set(atom,1);
    
    std::cout << "Joining thread!" << std::endl;
    this->polling_thread->join();
}

//--------------------------

void PollingThread::poll()
{
    while(this->finished == false)
    {
        struct mpd_status * new_status = mpd_run_status(this->mpd_con);
        if(new_status != NULL)
        {
            if((old_status == NULL) || (mpd_status_get_song_id(new_status) != mpd_status_get_song_id(old_status)))
            {
                g_printerr("Song changed\n");
                this->song_changed_callback(new_status);
            }

            struct mpd_status * to_free = old_status;
            old_status = new_status;
            if(to_free != NULL)
            {
                mpd_status_free(to_free);
            }
        }
        else
        {
            g_printerr("ConFail: %s\n", mpd_connection_get_error_message(this->mpd_con));
            if(new_status && mpd_status_get_error(new_status) != NULL)
            {
                g_printerr("error: %s\n", mpd_status_get_error(new_status));
            }
            break;
        }

        Glib::usleep(1000);
    }
    std::cout << "Done." << std::endl;
}

//--------------------------

static void print_tag(const struct mpd_song *song, enum mpd_tag_type type, const char *label)
{
      unsigned i = 0;
      const char *value;

      while ((value = mpd_song_get_tag(song, type, i++)) != NULL)
      {
            g_print("%s: %s\n", label, value);
      }
}

void PollingThread::song_changed_callback(struct mpd_status * status)
{
    struct mpd_song * song;
    mpd_send_current_song(this->mpd_con);
    while ((song = mpd_recv_song(this->mpd_con)) != NULL)
    {
        g_print("---------------------------------\n");
        g_print("uri: %s\n", mpd_song_get_uri(song));
        print_tag(song, MPD_TAG_ARTIST, "artist");
        print_tag(song, MPD_TAG_ALBUM, "album");
        print_tag(song, MPD_TAG_TITLE, "title");
        print_tag(song, MPD_TAG_TRACK, "track");
        print_tag(song, MPD_TAG_NAME, "name");
        print_tag(song, MPD_TAG_DATE, "date");

        if (mpd_song_get_duration(song) > 0) 
        {
            g_print("time: %u\n", mpd_song_get_duration(song));
        }

        g_print("pos: %u\n", mpd_song_get_pos(song));
        mpd_song_free(song);
    }
}















































    /*
       struct mpd_song *song;
       enum mpd_idle event;
       while(true)
       {
       event = mpd_run_idle(my_con.get_conn());
       printf("Received event: %s\n",mpd_idle_name(event));

       switch(event)
       {
       case MPD_IDLE_PLAYER: 
       { 
       mpd_status * status = mpd_run_status(my_con.get_conn());
       if(status != NULL)
       {

       mpd_song_free(song);
       }
       mpd_status_free(status);
       }
       else
       {
       cerr << "Could not get status" << endl;
       }

       break;
       }
       }
       }
       */
