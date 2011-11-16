#include "PlaybackButtons.hh"
#include "../Log/Writer.hh"
#include "../Utils/Utils.hh"

namespace GManager
{
    PlaybackButtons::PlaybackButtons(MPD::Client& instance, const Glib::RefPtr<Gtk::Builder>& builder) 
    {
        this->mp_Client = &instance;

        BUILDER_GET(builder,"stop_button",stop_button);
        BUILDER_GET(builder,"pause_button",pause_button);
        BUILDER_GET(builder,"prev_button",prev_button);
        BUILDER_GET(builder,"next_button",next_button);

        stop_button->signal_clicked().connect(sigc::mem_fun(*this,&PlaybackButtons::on_button_stop));
        pause_button->signal_clicked().connect(sigc::mem_fun(*this,&PlaybackButtons::on_button_pause));
        prev_button->signal_clicked().connect(sigc::mem_fun(*this,&PlaybackButtons::on_button_prev));
        next_button->signal_clicked().connect(sigc::mem_fun(*this,&PlaybackButtons::on_button_next));
    }

    //----------------------------

    PlaybackButtons::~PlaybackButtons(void)
    {
    }

    //----------------------------

    void PlaybackButtons::on_button_stop(void)
    {
        mp_Client->playback_stop();
    }

    //----------------------------

    void PlaybackButtons::on_button_pause(void)
    {
        mp_Client->playback_pause();
    }

    //----------------------------

    void PlaybackButtons::on_button_prev(void)
    {
        mp_Client->playback_prev();
    }

    //----------------------------

    void PlaybackButtons::on_button_next(void)
    {
        mp_Client->playback_next();
    }
}
