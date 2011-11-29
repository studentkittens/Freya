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
        Gtk::StatusIcon(Gtk::Stock::INFO)
    {
        mp_Client = &client;
        mp_Window = &main_window;

        set_tooltip_text("Freya Trayicon");
        set_visible(CONFIG_GET_AS_INT("settings.trayicon.totray"));
        m_refUIManager = Gtk::UIManager::create();
        m_refActionGroup = Gtk::ActionGroup::create();
        m_refUIManager->insert_action_group(m_refActionGroup);

        add_item(m_ActionNext,"next","Next","Play next song",Gtk::Stock::MEDIA_NEXT);
        add_item(m_ActionPrev,"prev","Prev","Play prev song",Gtk::Stock::MEDIA_PREVIOUS);
        add_item(m_ActionStop,"stop","Stop","Stop playing",Gtk::Stock::MEDIA_STOP);
        add_item(m_ActionPause,"pause","Pause","Pause playing",Gtk::Stock::MEDIA_PLAY);
        add_item(m_ActionQuit,"quit","Quit","Quit Freya fully",Gtk::Stock::QUIT);

        m_ActionNext->signal_activate().connect(sigc::mem_fun(*this,&Trayicon::on_next_clicked));
        m_ActionPrev->signal_activate().connect(sigc::mem_fun(*this,&Trayicon::on_prev_clicked));
        m_ActionStop->signal_activate().connect(sigc::mem_fun(*this,&Trayicon::on_stop_clicked));
        m_ActionPause->signal_activate().connect(sigc::mem_fun(*this,&Trayicon::on_pause_clicked));
        m_ActionQuit->signal_activate().connect(sigc::mem_fun(*this,&Trayicon::on_quit_clicked));

        m_refUIManager->add_ui_from_string(ui_info);
        m_Popup = (Gtk::Menu*)(m_refUIManager->get_widget("/PopupMenu"));

        /* Dirty hack to fix the strange huge icon */
        set(m_Popup->render_icon_pixbuf(Gtk::Stock::INFO,Gtk::ICON_SIZE_SMALL_TOOLBAR));
    }

    //-------------------------
    
    void Trayicon::add_item(Glib::RefPtr<Gtk::Action>& action,
            Glib::ustring item_name,
            Glib::ustring item_label,
            Glib::ustring item_tooltip,
            Gtk::StockID icon)
    {
        action = Gtk::Action::create(item_name,icon,item_label,item_tooltip);
        m_refActionGroup->add(action);
    }

    //-------------------------
    
    void Trayicon::on_popup_menu(guint button, guint32 activate_time)
    {
        m_Popup->popup(button,activate_time);
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
}
