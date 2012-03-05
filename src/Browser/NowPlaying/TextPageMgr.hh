#ifndef FREYA_TEXTPAGEMGR_HH
#define FREYA_TEXTPAGEMGR_HH

#include <gtkmm.h>
#include "UpdateInterface.hh"

namespace Browser
{
    class TextPageMgr : public Gtk::ScrolledWindow
    {
        public: 
            TextPageMgr(BaseObjectType* cobject, const Glib::RefPtr<Gtk::Builder>& builder);

        private:
            Gtk::TextView * textView;

    };
}

#endif /* end of include guard: FREYA_TEXTPAGEMGR_HH */

