#include "Trayicon.hh"
#include "../Log/Writer.hh"
#include "../Config/Handler.hh"

namespace GManager 
{
    Glib::ustring ui_info =
        "<ui>"
        "  <popup name='PopupMenu'>"
        "    <menuitem action='quit'/>"
        "    <separator />"
        "    <menuitem action='next'/>"
        "    <menuitem action='prev'/>"
        "    <menuitem action='stop'/>"
        "    <menuitem action='pause'/>"
        "    <separator />"
        "  </popup>"
        "</ui>";

    Trayicon::Trayicon(MPD::Client& client,Gtk::Window& main_window) :
        Gtk::StatusIcon(Gtk::Stock::INFO),
        Browser::BasePopup(NULL,ui_info),
        AbstractClientUser(client)
    {
        mp_Window = &main_window;

        set_tooltip_text("Freya Trayicon");
        set_visible(CONFIG_GET_AS_INT("settings.trayicon.totray"));

        menu_add_item(m_ActionNext,"next","Next","Play next song",Gtk::Stock::MEDIA_NEXT);
        menu_add_item(m_ActionPrev,"prev","Prev","Play prev song",Gtk::Stock::MEDIA_PREVIOUS);
        menu_add_item(m_ActionStop,"stop","Stop","Stop playing",Gtk::Stock::MEDIA_STOP);
        menu_add_item(m_ActionPause,"pause","Pause","Pause playing",Gtk::Stock::MEDIA_PLAY);
        menu_add_item(m_ActionQuit,"quit","Quit","Quit Freya fully",Gtk::Stock::QUIT);
        menu_construct("PopupMenu");

        m_ActionNext->signal_activate().connect(sigc::mem_fun(*this,&Trayicon::on_next_clicked));
        m_ActionPrev->signal_activate().connect(sigc::mem_fun(*this,&Trayicon::on_prev_clicked));
        m_ActionStop->signal_activate().connect(sigc::mem_fun(*this,&Trayicon::on_stop_clicked));
        m_ActionPause->signal_activate().connect(sigc::mem_fun(*this,&Trayicon::on_pause_clicked));
        m_ActionQuit->signal_activate().connect(sigc::mem_fun(*this,&Trayicon::on_quit_clicked));

        /* Dirty hack to fix the strange huge icon */
        set(mp_Popup->render_icon_pixbuf(Gtk::Stock::INFO,Gtk::ICON_SIZE_LARGE_TOOLBAR));
    }

    //-------------------------
    
    void Trayicon::on_popup_menu(guint button, guint32 activate_time)
    {
        mp_Popup->popup(button,activate_time);
    }
    
    //---------------------------

    void Trayicon::on_activate(void)
    {
        mp_Window->set_visible(!mp_Window->get_visible());
    }

    //---------------------------

    void Trayicon::on_next_clicked(void)
    {
        mp_Client->playback_next();
    }
    
    //---------------------------
    
    void Trayicon::on_prev_clicked(void)
    {
        mp_Client->playback_prev();
    }
    
    //---------------------------
    
    void Trayicon::on_stop_clicked(void)
    {
        mp_Client->playback_stop();
    }
    
    //---------------------------
    
    void Trayicon::on_pause_clicked(void)
    {
        mp_Client->playback_pause();
    }
    
    //---------------------------
    
    void Trayicon::on_quit_clicked(void)
    {
        Gtk::Main::quit();
    }

    //---------------------------
    
    void Trayicon::on_connection_change(bool is_connected)
    {
        /*
        // For some reason this crashes on disconnect.
        // Huh?
        m_ActionNext->set_sensitive(is_connected);
        m_ActionPrev->set_sensitive(is_connected);
        m_ActionStop->set_sensitive(is_connected);
        m_ActionPause->set_sensitive(is_connected);
        */
    }
    
    //---------------------------
            
    void Trayicon::on_client_update(enum mpd_idle event, MPD::NotifyData& data)
    {
        MPD::Status& status = data.get_status();
        if(status.get_state() == MPD_STATE_PLAY)
        {
            m_ActionPause->set_stock_id(Gtk::Stock::MEDIA_PAUSE);
            m_ActionPause->set_label("Pause");
        }
        else
        {
            m_ActionPause->set_stock_id(Gtk::Stock::MEDIA_PLAY);
            m_ActionPause->set_label("Play");
        }
    }

    //---------------------------
}
