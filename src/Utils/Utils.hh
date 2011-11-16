#ifndef FREYA_UTILS_GUARD
#define FREYA_UTILS_GUARD

#define BUILDER_GET(builder_refp, widget_name, widget_ptr) \
    builder_refp->get_widget(widget_name,widget_ptr);      \
    g_assert(widget_ptr);                                  \
    Gtk::manage(widget_ptr);                               

#endif
