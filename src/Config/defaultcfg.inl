#ifndef DEFAULTCFG_QANZVJMD
#define DEFAULTCFG_QANZVJMD
/*
#ifndef _GLIBMM_USTRING_H
#include <glibmm/ustring.h>

#endif
*/
#include <glibmm/ustring.h>
const Glib::ustring defaultconfig(
	"<?xml version=\"1.0\" encoding=\"utf-8\"?>"
	"<freya>"
	"    <settings>"
	"        <connection>"
	"            <port>6600</port>"
	"            <musicroot>~/chris/Musik</musicroot>"
	"            <host>myFriendIsAMadCow....</host>"
	"            <autoconnect>1</autoconnect>"
	"            <stoponexit>1</stoponexit>"
	"            <reconnecttimeout>2</reconnecttimeout>"
	"        </connection>"
	"        <libnotify>"
	"            <signal>0</signal>"
	"        </libnotify>"
	"    </settings>"
	"    <plugins>"
	"        <glyr>"
	"            <artimg>5</artimg>"
	"            <artbio>0</artbio>"
	"            <provider>all</provider>"
	"        </glyr>"
	"        <plugindummy>"
	"            <option1>0</option1>"
	"            <option2>5</option2>"
	"            <option3>dummy</option3>"
	"        </plugindummy>"
	"    </plugins>"
	"</freya>"
);


#endif /* end of include guard: DEFAULTCFG_QANZVJMD */
