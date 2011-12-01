#ifndef STATBROWSER_H0M8CVQP

#define STATBROWSER_H0M8CVQP

#include "../AbstractBrowser.hh"
#include "../MPD/Client.hh"
#include <gtkmm.h>
#include "../Utils/Utils.hh"
namespace Browser {
    class StatBrowser : public Gtk::Frame, public AbstractBrowser {
        public:
            StatBrowser (MPD::Client&, Glib::RefPtr<Gtk::Builder>&);
            ~StatBrowser ();
            

            /**
             * @brief simple getter function for gtk widget
             *
             * @return gtk widget ptr to _this_ container widget
             */
            Gtk::Widget * get_container(void);

        private:
            /* label members for statistics*/
            Gtk::Label *noofartist, *noofalbums, *noofsongs, *dbplaytime, *playtime, *dbupdate, *uptime;
            void on_client_update(enum mpd_idle event, MPD::NotifyData& data);
    };
}
#endif /* end of include guard: STATBROWSER_H0M8CVQP */


