#include "PlaybackButtons.hh"
#include "../Log/Writer.hh"
#include "../Utils/Utils.hh"

namespace GManager
{
    PlaybackButtons::PlaybackButtons(MPD::Client& instance, const Glib::RefPtr<Gtk::Builder>& builder) :
        AbstractClientUser(instance), 
        play_icon(Gtk::Stock::MEDIA_PLAY,Gtk::ICON_SIZE_BUTTON), 
        pause_icon(Gtk::Stock::MEDIA_PAUSE,Gtk::ICON_SIZE_BUTTON)
    {
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

    //----------------------------

    void PlaybackButtons::on_client_update(enum mpd_idle event, MPD::NotifyData& data)
    {
        if(event & MPD_IDLE_PLAYER)
        {
            pause_button->set_image((data.get_status().get_state() == MPD_STATE_PLAY) ? pause_icon : play_icon);
        }
    }
    
    //----------------------------

    void PlaybackButtons::on_connection_change(bool is_connected) 
    {
       stop_button->set_sensitive(is_connected);
       prev_button->set_sensitive(is_connected);
       next_button->set_sensitive(is_connected);
       pause_button->set_sensitive(is_connected);
    }
}
