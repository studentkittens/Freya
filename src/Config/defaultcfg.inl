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
            "            <stoponexit>1</stoponexit>\n"
            "            <timeout>20</timeout>\n"
            "            <reconnectinterval>2</reconnectinterval>\n"
            "        </connection>\n"
            "        <libnotify>\n"
            "            <signal>0</signal>\n"
            "            <timeout>-1</timeout>\n"
            "        </libnotify>\n"
            "        <trayicon>\n"
            "            <totray>0</totray>\n"
            "        </trayicon>\n"
            "        <playback>\n"
            "            <crossfade>0</crossfade>\n"
            "            <stoponexit>0</stoponexit>\n"
            "        </playback>\n"
            "    </settings>\n"
            "    <plugins>\n"
            "        <glyr>\n"
            "            <artimg>5</artimg>\n"
            "            <artbio>0</artbio>\n"
            "            <provider>all</provider>\n"
            "        </glyr>\n"
            "        <plugindummy>\n"
            "            <option1>0</option1>\n"
            "            <option2>5</option2>\n"
            "            <option3>dummy</option3>\n"
            "        </plugindummy>\n"
            "    </plugins>\n"
            "</freya>\n"
            );
}

#endif /* end of include guard: DEFAULTCFG_QANZVJMD */
