#include "QueuePopup.hh"

namespace Browser
{
    static Glib::ustring ui_info =
        "<ui>"
        "  <popup name='QueuePopupMenu'>"
        "    <menuitem action='remove'/>"
        "    <menuitem action='playlist_add'/>"
        "    <menuitem action='clear'/>"
        "  </popup>"
        "</ui>";

    QueuePopup::QueuePopup(Gtk::Widget& to_register) : BasePopup(to_register,ui_info)
    {
        menu_add_item(m_ActionDel,"remove","Remove","Remove selected Songs",Gtk::Stock::DELETE);
        menu_add_item(m_ActionDel,"playlist_add","Add to playlist","Add to a certain playlist",Gtk::Stock::JUMP_TO);
        menu_add_item(m_ActionClear,"clear","Clear","Clear Queue",Gtk::Stock::CLEAR);
        menu_construct("QueuePopupMenu");
    }
}
