#include "TracklistMgr.hh"
#include "../../MPD/BaseClient.hh"

namespace Browser
{
TracklistMgr::TracklistMgr(BaseObjectType* cobject, const Glib::RefPtr<Gtk::Builder>& builder)
    : Gtk::Expander(cobject),
      txtWall(15,2)
{
    add(txtWall);
}

/////////////////////////////////

void TracklistMgr::update(MPD::Client& client, mpd_idle event, MPD::NotifyData& data)
{
    if(event & MPD_IDLE_PLAYER)
    {
        MPD::Song  * curr = data.get_song();
        if(curr != NULL)
        {
            MPD::Query * dbq  = client.create_db_songs_query();
            if(dbq != NULL)
            {
                txtWall.clear();
                MPD::SongVector list;
                dbq->add_tag_constraint(MPD_TAG_ARTIST,curr->get_tag(MPD_TAG_ARTIST));
                dbq->add_tag_constraint(MPD_TAG_ALBUM, curr->get_tag(MPD_TAG_ALBUM));
                dbq->commit(list);
                for(MPD::SongVector::iterator it = list.begin(); it != list.end(); it++)
                {
                    MPD::Song * track = *it;
                    txtWall.add(*Gtk::manage(new Gtk::LinkButton("no link.",track->get_tag(MPD_TAG_TITLE))));
                    delete track;
                }
                delete dbq;
            }
        }
    }
}
}
