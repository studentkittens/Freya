#ifndef FREYA_DEFAULTCFG_QANZVJMD
#define FREYA_DEFAULTCFG_QANZVJMD
#include <glibmm/ustring.h>

namespace Config
{
    static const Glib::ustring defaultconfig(
            "<?xml version=\"1.0\" encoding=\"utf-8\"?>\n"
            "<freya>\n"
            "    <settings>\n"
            "        <connection>\n"
            "            <port>6600</port>\n"
            "            <musicroot>~/chris/Musik</musicroot>\n"
            "            <host>localhost</host>\n"
            "            <!-- Connect on startup? -->"
            "            <autoconnect>1</autoconnect>\n"
            "            <!-- In seconds -->"
            "            <timeout>20</timeout>\n"
            "             <!-- Autoreconnect interval in seconds -->"
            "            <reconnectinterval>2</reconnectinterval>\n"
            "        </connection>\n"
            "        <libnotify>\n"
            "           <!-- Show notifications? -->"
            "            <signal>0</signal>\n"
            "           <!-- How long? -->"
            "            <timeout>-1</timeout>\n"
            "        </libnotify>\n"
            "        <trayicon>\n"
            "            <!-- Show trayicon? -->"
            "            <tray>0</tray>\n"
            "            <!-- To tray when closing? -->"
            "            <totrayonclose>0</totrayonclose>\n"
            "        </trayicon>\n"
            "        <playback>\n"
            "            <!-- Stop music when closing Freya? -->"
            "            <stoponexit>0</stoponexit>\n"
            "        </playback>\n"
            "    </settings>\n"
            "    <plugins>\n"
            "    </plugins>\n"
            "</freya>\n"
            );
}

#endif /* end of include guard: DEFAULTCFG_QANZVJMD */
