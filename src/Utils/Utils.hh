#ifndef FREYA_UTILS_GUARD
#define FREYA_UTILS_GUARD

#include <glibmm.h>

/* Gtk::Builder macros */
#define BUILDER_GET(builder_refp, widget_name, widget_ptr) \
    BUILDER_GET_NO_MANAGE(builder_refp, widget_name, widget_ptr) \
    Gtk::manage(widget_ptr);                               

#define BUILDER_GET_NO_MANAGE(builder_refp, widget_name, widget_ptr) \
    widget_ptr = NULL;                                     \
    builder_refp->get_widget(widget_name,widget_ptr);      \
    g_assert(widget_ptr);                                  \


#define BUILDER_ADD(builder_ref, filename)   \
    g_assert(filename);                      \
    try {                                    \
     builder_ref->add_from_file(filename);   \
    } catch(const Gtk::BuilderError& e) {    \
     Error("Could not add playlist ui"       \
           "definitions to builder. => %s"   \
           "| Is '%s' there and okay?",      \
           e.what().c_str(),filename);       \
    }  
namespace Utils
{
    Glib::ustring seconds_to_duration(unsigned long);
    Glib::ustring seconds_to_timestamp(const long);
}
#endif       
