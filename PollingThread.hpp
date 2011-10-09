#include <iostream>
#include <glibmm/random.h>
#include <glibmm/thread.h>
#include <glibmm/timer.h>

#include <mpd/client.h>
#include <mpd/status.h>
#include <mpd/entity.h>
#include <mpd/search.h>
#include <mpd/tag.h>

class PollingThread : public sigc::trackable 
{
    public:
    PollingThread() {};
    PollingThread(struct mpd_connection * mpd_con);
    ~PollingThread();

    void poll();
    void finish();

    private:
    struct mpd_connection * mpd_con;
    struct mpd_status * old_status;
    Glib::Thread * polling_thread;
    bool finished;
    void song_changed_callback(struct mpd_status * status);
};
