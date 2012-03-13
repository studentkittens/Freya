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

            void set_request_type(GLYR_GET_TYPE type);
    
            void on_deliver(GlyrMemCache * list);

        private:
            Gtk::TextView * textView;
            GLYR_GET_TYPE type;

    };
}

#endif /* end of include guard: FREYA_TEXTPAGEMGR_HH */

