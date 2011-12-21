#ifndef FREYA_SETTINGS_OUTPUTS_GUARD
#define FREYA_SETTINGS_OUTPUTS_GUARD

#include <gtkmm.h>

#include "SettingsSub.hh"
#include "OutputsModelColumns.hh"
#include "../MPD/AbstractItemlist.hh"
#include "../MPD/AbstractClientUser.hh"
#include "../MPD/Client.hh"
#include "../Utils/Utils.hh"

namespace Browser
{
    class Settings;
    class SettingsOutputs : public SettingsSub, public AbstractItemlist, public AbstractClientUser
    {
        public:
            SettingsOutputs(MPD::Client &client,const Glib::RefPtr<Gtk::Builder> &builder, Browser::Settings * sett);
            ~SettingsOutputs();

            void accept_new_settings(void);
            void decline_new_settings(void);
            void reset_settings(void);
            void add_item(void *item);
        protected:
            void on_client_update(enum mpd_idle event, MPD::NotifyData& data);
            void on_connection_change(bool);
            void on_toggle(const Glib::ustring& path);
        private:
            Glib::RefPtr<Gtk::ListStore> treeModel;
            Gtk::TreeView * treeViewPtr;
            OutputsModelColumns treeColumns;
            MPD::Client* client;
            Settings *sett;
            bool running;
    };


}




#endif