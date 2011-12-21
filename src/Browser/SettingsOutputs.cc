#include "SettingsOutputs.hh"
#include "Settings.hh"
#include "../MPD/AudioOutput.hh"
#include "../Log/Writer.hh"
namespace Browser
{

    SettingsOutputs::SettingsOutputs(MPD::Client &client,const Glib::RefPtr<Gtk::Builder> &builder, Browser::Settings * sett)
    : AbstractClientUser(client), running(false)
    {
        this->sett = sett;
        BUILDER_GET(builder,"output_treeView",treeViewPtr);

        treeModel = Gtk::ListStore::create(treeColumns);
        treeViewPtr->set_model(treeModel);
        treeViewPtr->set_headers_visible(false);


        treeViewPtr->append_column_editable("",treeColumns.colActive);
        treeViewPtr->append_column("",treeColumns.colName);

        Gtk::CellRendererToggle *cell = (Gtk::CellRendererToggle*) treeViewPtr->get_column_cell_renderer(0);
        cell->set_activatable(true);
        cell->signal_toggled().connect(sigc::mem_fun(*this,&Browser::SettingsOutputs::on_toggle));
    }


    SettingsOutputs::~SettingsOutputs(){}

    void SettingsOutputs::on_toggle(const Glib::ustring& path)
    {
        sett->settings_changed();
    }

    void SettingsOutputs::on_client_update(enum mpd_idle event, MPD::NotifyData &data)
    {
        if(!running && (event & (MPD_IDLE_OUTPUT)))
        {
            treeModel->clear();
            mp_Client->fill_outputs(*this);
        }
    }

    void SettingsOutputs::on_connection_change(bool is_connected)
    {
        if(!is_connected)
            treeViewPtr->set_sensitive(false);
        else
            treeViewPtr->set_sensitive(true);
    }

    void SettingsOutputs::decline_new_settings(void)
    {
        reset_settings();
    }

    void SettingsOutputs::accept_new_settings(void)
    {
            running=true;
            typedef Gtk::TreeModel::Children type_children;
            type_children children = treeModel->children();
            for(type_children::iterator iter = children.begin();iter != children.end(); ++iter)
            {
                Gtk::TreeModel::Row row = *iter;
                if(row[treeColumns.colActive])
                    (*(row[treeColumns.colOutput])).enable();
                else
                    (*(row[treeColumns.colOutput])).disable();
            }
            treeModel->clear();
            mp_Client->fill_outputs(*this);

            running=false;
    }

    void SettingsOutputs::reset_settings(void)
    {
        running=true;
        typedef Gtk::TreeModel::Children type_children;
        type_children children = treeModel->children();
        for(type_children::iterator iter = children.begin();iter != children.end(); ++iter)
        {
            Gtk::TreeModel::Row row = *iter;
            row[treeColumns.colActive] = (*(row[treeColumns.colOutput])).get_enabled();
        }
        running=false;
    }

    void SettingsOutputs::add_item(void * item)
    {
        MPD::AudioOutput* a_item = (MPD::AudioOutput*) item;
        Gtk::TreeModel::Row row = *(treeModel->append());
        row[treeColumns.colName] = a_item->get_name();
        row[treeColumns.colActive] = a_item->get_enabled();
        row[treeColumns.colOutput] = a_item;
    }
}