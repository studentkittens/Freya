#include "QueuePopup.hh"

namespace Browser
{
    static Glib::ustring ui_info =
        "<ui>"
        "  <popup name='QueuePopupMenu'>"
        "    <menuitem action='q_remove'/>"
        "    <menuitem action='q_clear'/>"
        "    <separator />"
        "    <menuitem action='q_add_as_pl'/>"
        "  </popup>"
        "</ui>";

    QueuePopup::QueuePopup(Gtk::Widget& to_register) : BasePopup(&to_register,ui_info)
    {
        menu_add_item(m_ActionDel,"q_remove","Remove","Remove selected Songs",Gtk::Stock::DELETE);
        menu_add_item(m_ActionDel,"q_add_as_pl","Save as Playlist","Save current queue as a playlist",Gtk::Stock::JUMP_TO);
        menu_add_item(m_ActionClear,"q_clear","Clear","Clear Queue",Gtk::Stock::CLEAR);
        menu_construct("QueuePopupMenu");
    }
}
