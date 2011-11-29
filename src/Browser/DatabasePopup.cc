#include "DatabasePopup.hh"

namespace Browser
{
    static Glib::ustring ui_info =
        "<ui>"
        "  <popup name='DatabasePopupMenu'>"
        "    <menuitem action='db_add'/>"
        "    <menuitem action='db_add_to_playlist'/>"
        "    <separator />"
        "    <menuitem action='db_replace'/>"
        "    <separator />"
        "    <menuitem action='db_refresh'/>"
        "  </popup>"
        "</ui>";

    DatabasePopup::DatabasePopup(Gtk::Widget& to_register) : BasePopup(to_register,ui_info)
    {
        menu_add_item(m_ActionAdd,"db_add","Add Playlist","add to queue",Gtk::Stock::ADD);
        menu_add_item(m_ActionAddToPL,"db_add_to_playlist","Add to","Add to a certain playlist",Gtk::Stock::GOTO_LAST);
        menu_add_item(m_ActionReplace,"db_replace","Replace","remove selected playlists",Gtk::Stock::JUMP_TO);
        menu_add_item(m_ActionRefresh,"db_refresh","Refresh","remove selected playlists",Gtk::Stock::REFRESH);
        menu_construct("DatabasePopupMenu");
    }
}
