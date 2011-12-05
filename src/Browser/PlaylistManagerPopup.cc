#include "PlaylistManagerPopup.hh"

namespace Browser
{
    static Glib::ustring pl_ui_info =
        "<ui>"
        "  <popup name='PlaylistmanagerPopupMenu'>"
        "    <menuitem action='pl_append'/>"
        "    <menuitem action='pl_replace'/>"
        "    <separator />"
        "    <menuitem action='pl_delete'/>"
        "    <separator />"
        "  </popup>"
        "</ui>";

    PlaylistManagerPopup::PlaylistManagerPopup(Gtk::Widget& to_register) : BasePopup(&to_register,pl_ui_info)
    {
        menu_add_item(m_ActionAdd,"pl_append","Append","Append to Queue",Gtk::Stock::ADD);
        menu_add_item(m_ActionRepl,"pl_replace","Replace","Replace Queue contents",Gtk::Stock::JUMP_TO);
        menu_add_item(m_ActionDel,"pl_delete","Remove Playlist","Remove this Playlist",Gtk::Stock::DELETE);
        menu_construct("PlaylistmanagerPopupMenu");
    }
}
