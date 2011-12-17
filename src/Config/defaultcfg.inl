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
            "            <autoconnect>1</autoconnect>\n"
            "            <timeout>20</timeout>\n"
            "            <reconnectinterval>2</reconnectinterval>\n"
            "        </connection>\n"
            "        <libnotify>\n"
            "            <signal>0</signal>\n"
            "            <timeout>-1</timeout>\n"
            "        </libnotify>\n"
            "        <trayicon>\n"
            "            <totray>0</totray>\n"
            "            <totrayonclose>0</totrayonclose>\n"
            "        </trayicon>\n"
            "        <playback>\n"
            "            <stoponexit>0</stoponexit>\n"
            "        </playback>\n"
            "    </settings>\n"
            "    <plugins>\n"
            "    </plugins>\n"
            "</freya>\n"
            );
}

#endif /* end of include guard: DEFAULTCFG_QANZVJMD */
