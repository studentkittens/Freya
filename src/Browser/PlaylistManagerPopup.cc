#include "PlaylistManagerPopup.hh"

namespace Browser
{
    static Glib::ustring pl_ui_info =
        "<ui>"
        "  <popup name='PlaylistmanagerPopupMenu'>"
        "    <menuitem action='pl_add'/>"
        "    <menuitem action='pl_replace'/>"
        "    <separator />"
        "    <menuitem action='pl_rename'/>"
        "    <menuitem action='pl_delete'/>"
        "    <separator />"
        "  </popup>"
        "</ui>";

    PlaylistManagerPopup::PlaylistManagerPopup(Gtk::Widget& to_register) : BasePopup(&to_register,pl_ui_info)
    {
        menu_add_item(m_ActionAdd,"pl_add","Append","Append to Queue",Gtk::Stock::ADD);
        menu_add_item(m_ActionRepl,"pl_replace","Replace","Replace Queue contents",Gtk::Stock::JUMP_TO);
        menu_add_item(m_ActionDel,"pl_delete","Remove Playlist","Remove this Playlist",Gtk::Stock::DELETE);
        menu_add_item(m_ActionRename,"pl_rename","Rename Playlist","Rename this playlist",Gtk::Stock::EDIT);
        menu_construct("PlaylistmanagerPopupMenu");
    }
}
