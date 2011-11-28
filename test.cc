#include <gtkmm.h>


class Trayicon : public Gtk::StatusIcon
{
    public:
        Trayicon(void);
        ~Trayicon(void);

    private:

        void add_item(Glib::RefPtr<Gtk::Action>& action,
                      Glib::ustring item_name,
                      Glib::ustring item_label,
                      Glib::ustring item_tooltip,
                      Gtk::StockID icon);

        void on_activate(void);
        void on_popup_menu (guint button, guint32 activate_time);

        Gtk::Menu * m_Popup;
        Glib::RefPtr<Gtk::UIManager> m_refUIManager;
        Glib::RefPtr<Gtk::ActionGroup> m_refActionGroup;
        Glib::RefPtr<Gtk::Action> m_ActionNext;
        Glib::RefPtr<Gtk::Action> m_ActionPrev;
        Glib::RefPtr<Gtk::Action> m_ActionStop;
        Glib::RefPtr<Gtk::Action> m_ActionPause;
        Glib::RefPtr<Gtk::Action> m_ActionQuit;

};

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


//-------------------

void Trayicon::add_item(Glib::RefPtr<Gtk::Action>& action,
        Glib::ustring item_name,
        Glib::ustring item_label,
        Glib::ustring item_tooltip,
        Gtk::StockID icon)
{
    action = Gtk::Action::create(item_name,icon,item_label,item_tooltip);
    m_refActionGroup->add(action);
}

Trayicon::Trayicon(void) :
    Gtk::StatusIcon(Gtk::Stock::INFO)
{

    set_tooltip_text("Freya Trayicon");
    m_refUIManager = Gtk::UIManager::create();
    m_refActionGroup = Gtk::ActionGroup::create();

    add_item(m_ActionNext,"next","Next","Play next song",Gtk::Stock::MEDIA_NEXT);
    add_item(m_ActionPrev,"prev","Prev","Play prev song",Gtk::Stock::MEDIA_PREVIOUS);
    add_item(m_ActionStop,"stop","Stop","Stop playing",Gtk::Stock::MEDIA_STOP);
    add_item(m_ActionPause,"pause","Pause","Pause playing",Gtk::Stock::MEDIA_PLAY);
    add_item(m_ActionQuit,"quit","Quit","Quit Freya fully",Gtk::Stock::QUIT);

    m_refUIManager->insert_action_group(m_refActionGroup);
    m_refUIManager->add_ui_from_string(ui_info);
    m_Popup = (Gtk::Menu*)(m_refUIManager->get_widget("/PopupMenu"));

    /* Dirty hack to fix the strange huge icon */
    set(m_Popup->render_icon_pixbuf(Gtk::Stock::INFO,Gtk::ICON_SIZE_SMALL_TOOLBAR));
}

Trayicon::~Trayicon(void)
{
}

void Trayicon::on_activate(void)
{
    g_message("Clicked.");
}

void Trayicon::on_popup_menu(guint button, guint32 activate_time)
{
    g_message("Popup.");
    m_Popup->popup(button,activate_time);
}


int main(int argc, char *argv[])
{
    Gtk::Main kit(argc, argv);


    Trayicon t;

    //Show a window:
    //The program will stop, and the status icon will disappear, when the window
    //is closed.
    Gtk::Window window;
    window.set_title("gtkmm StatusIcon example.");
    window.set_default_size(300, 300);
    Gtk::Main::run(window); //Shows the window and returns when it is closed.

    return 0;
}
