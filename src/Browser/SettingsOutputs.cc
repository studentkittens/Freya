#include "SettingsOutputs.hh"
#include "Settings.hh"
#include "../MPD/AudioOutput.hh"
#include "../Log/Writer.hh"
namespace Browser
{

    SettingsOutputs::SettingsOutputs(MPD::Client &client,const Glib::RefPtr<Gtk::Builder> &builder, Browser::Settings * sett)
    : AbstractClientUser(client)
    {
        BUILDER_GET(builder,"output_treeView",treeViewPtr);

        treeModel = Gtk::ListStore::create(treeColumns);
        treeViewPtr->set_model(treeModel);
        treeViewPtr->append_column("",treeColumns.colName);
        treeViewPtr->append_column("",treeColumns.colActive);

    }


    SettingsOutputs::~SettingsOutputs(){}


    void SettingsOutputs::on_client_update(enum mpd_idle event, MPD::NotifyData &data)
    {
        if(event & (MPD_IDLE_PLAYER))
        {
            treeModel->clear();
            mp_Client->fill_outputs(*this);
        }
    }

    void SettingsOutputs::on_connection_change(bool is_connected)
    {
    }

    void SettingsOutputs::decline_new_settings(void)
    {
        
    }

    void SettingsOutputs::accept_new_settings(void)
    {
        
    }

    void SettingsOutputs::reset_settings(void)
    {
        
    }

    void SettingsOutputs::add_item(void * item)
    {
        MPD::AudioOutput* a_item = (MPD::AudioOutput*) item;
        Gtk::TreeModel::Row row = *(treeModel->append());
        row[treeColumns.colName] = a_item->get_name();
        row[treeColumns.colActive] = a_item->get_enabled();
    }
}