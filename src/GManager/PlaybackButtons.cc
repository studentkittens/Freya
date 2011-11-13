#include "PlaybackButtons.hh"
#include "../Log/Writer.hh"

namespace GManager
{
    PlaybackButtons::PlaybackButtons(MPD::Client * instance, const Glib::RefPtr<Gtk::Builder>& builder) 
    {
        try
        {
            g_assert(instance);
            this->client_instance = instance;

            builder->get_widget("stop_button",stop_button);
            builder->get_widget("play_button",play_button);
            builder->get_widget("pause_button",pause_button);
            builder->get_widget("prev_button",prev_button);
            builder->get_widget("next_button",next_button);

            Gtk::manage(stop_button);
            Gtk::manage(play_button);
            Gtk::manage(pause_button);
            Gtk::manage(prev_button);
            Gtk::manage(next_button);

            stop_button->signal_clicked().connect(sigc::mem_fun(*this,&PlaybackButtons::on_button_stop));
            play_button->signal_clicked().connect(sigc::mem_fun(*this,&PlaybackButtons::on_button_play));
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
        client_instance->playback_stop();
    }

    //----------------------------

    void PlaybackButtons::on_button_play(void)
    {
        client_instance->playback_play();
    }

    //----------------------------

    void PlaybackButtons::on_button_pause(void)
    {
        client_instance->playback_pause();
    }

    //----------------------------

    void PlaybackButtons::on_button_prev(void)
    {
        client_instance->playback_prev();
    }

    //----------------------------

    void PlaybackButtons::on_button_next(void)
    {
        client_instance->playback_next();
    }
}
