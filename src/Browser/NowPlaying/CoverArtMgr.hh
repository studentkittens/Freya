#ifndef FREYA_COVERARTMGR_HH
#define FREYA_COVERARTMGR_HH

#include <gtkmm.h>
#include "../../MPD/AbstractClientUser.hh"

namespace Browser
{
    class CoverArtMgr : public Gtk::Expander 
    {
        public:
            CoverArtMgr(BaseObjectType* cobject, const Glib::RefPtr<Gtk::Builder>& builder);
            ~CoverArtMgr();

        protected:

            void on_client_update(mpd_idle events, MPD::NotifyData& data);
            void on_connection_change(bool,bool) {}
            
        private:

            Gtk::Label * mp_ArtistLabel, 
                * mp_AlbumLabel,
                * mp_TitleLabel,
                * mp_YearLabel;

            EventImage * coverArt;
    };
}

#endif /* end of include guard: FREYA_COVERARTMGR_HH */

