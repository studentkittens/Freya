#ifndef FREYA_TEXTPAGEMGR_HH
#define FREYA_TEXTPAGEMGR_HH

#include <gtkmm.h>
#include "../../Glyr/UpdateInterface.hh"

namespace Browser
{
    class TextPageMgr : public Gtk::ScrolledWindow, public Glyr::UpdateInterface
    {
        public: 
            TextPageMgr(BaseObjectType* cobject, const Glib::RefPtr<Gtk::Builder>& builder);
            
            void update(MPD::Client& client, mpd_idle events, MPD::NotifyData& data);

        private:
            Gtk::TextView * textView;

    };
}

#endif /* end of include guard: FREYA_TEXTPAGEMGR_HH */

