#ifndef FREYA_COVERARTMGR_HH
#define FREYA_COVERARTMGR_HH

#include <gtkmm.h>
#include "../../MPD/AbstractClientUser.hh"
#include "EventImage.hh"
#include "UpdateInterface.hh"

namespace Browser
{
    class CoverArtMgr : public Gtk::Expander, public UpdateInterface
    {
        public:
            CoverArtMgr(BaseObjectType* cobject, const Glib::RefPtr<Gtk::Builder>& builder);
            ~CoverArtMgr();

        protected:

            void update(MPD::Client& client, mpd_idle event, MPD::NotifyData& data);
            
        private:

            Gtk::Label * mp_ArtistLabel, 
                * mp_AlbumLabel,
                * mp_TitleLabel,
                * mp_YearLabel;

            EventImage * coverArt;
    };
}

#endif /* end of include guard: FREYA_COVERARTMGR_HH */

