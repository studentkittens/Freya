#include "PlaybackButtons.hh"
#include "../Log/Writer.hh"

namespace GManager
{
    PlaybackButtons::PlaybackButtons(MPD::Client& instance, const Glib::RefPtr<Gtk::Builder>& builder) 
    {
        try
        {
            this->mp_Client = &instance;

            builder->get_widget("stop_button",stop_button);
            builder->get_widget("pause_button",pause_button);
            builder->get_widget("prev_button",prev_button);
            builder->get_widget("next_button",next_button);

            Gtk::manage(stop_button);
            Gtk::manage(pause_button);
            Gtk::manage(prev_button);
            Gtk::manage(next_button);

            stop_button->signal_clicked().connect(sigc::mem_fun(*this,&PlaybackButtons::on_button_stop));
            pause_button->signal_clicked().connect(sigc::mem_fun(*this,&PlaybackButtons::on_button_pause));
            prev_button->signal_clicked().connect(sigc::mem_fun(*this,&PlaybackButtons::on_button_prev));
            next_button->signal_clicked().connect(sigc::mem_fun(*this,&PlaybackButtons::on_button_next));
        }
        catch(const Gtk::BuilderError& e)
        {
            Error("BuilderFailure: %s",e.what().c_str());
        }
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
