#include "DatabasePopup.hh"

namespace Browser
{
    static Glib::ustring ui_info =
        "<ui>"
        "  <popup name='DatabasePopupMenu'>"
        "    <menuitem action='db_add'/>"
        "    <separator />"
        "    <menuitem action='db_replace'/>"
        "    <separator />"
        "    <menuitem action='db_update'/>"
        "    <menuitem action='db_rescan'/>"
        "  </popup>"
        "</ui>";

    DatabasePopup::DatabasePopup(Gtk::Widget& to_register) : BasePopup(&to_register,ui_info)
    {
        menu_add_item(m_ActionAdd,"db_add","Add","Add to Queue",Gtk::Stock::ADD);
        menu_add_item(m_ActionReplace,"db_replace","Replace","remove selected playlists",Gtk::Stock::JUMP_TO);
        menu_add_item(m_ActionUpdate,"db_update","Update","Update database",Gtk::Stock::REFRESH);
        menu_add_item(m_ActionRescan,"db_rescan","Rescan","Rescan database",Gtk::Stock::REFRESH);
        menu_construct("DatabasePopupMenu");
    }
}
