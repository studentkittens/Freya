#include "RelatedLinksMgr.hh"

namespace Browser
{
    RelatedLinksMgr::RelatedLinksMgr(BaseObjectType* cobject, const Glib::RefPtr<Gtk::Builder>& builder)
        : Gtk::Expander(cobject),
          txtWall(10,2)
    {
        add(txtWall);
        txtWall.add(*Gtk::manage(new Gtk::LinkButton("http://www.google.de","Wikipedia Artist")));
        txtWall.add(*Gtk::manage(new Gtk::LinkButton("http://www.google.de","Wikipedia Album")));
        txtWall.add(*Gtk::manage(new Gtk::LinkButton("http://www.google.de","Last.fm Page")));
        txtWall.add(*Gtk::manage(new Gtk::LinkButton("http://www.google.de","AllMusic Page")));
    }

    /////////////////////////////////

    void RelatedLinksMgr::update(MPD::Client& client, mpd_idle event, MPD::NotifyData& data)
    {
    }
}
