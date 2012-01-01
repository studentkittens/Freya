 /***********************************************************
* This file is part of Freya 
* - A free MPD Gtk3 MPD Client -
* 
* Authors: Christopher Pahl, Christoph Piechula,
*          Eduard Schneider, Marc Tigges
*
* Copyright (C) [2011-2012]
* Hosted at: https://github.com/studentkittens/Freya
*
*              __..--''``---....___   _..._    __
*    /// //_.-'    .-/";  `        ``<._  ``.''_ `. / // /
*   ///_.-' _..--.'_                        `( ) ) // //
*   / (_..-' // (< _     ;_..__               ; `' / ///
*    / // // //  `-._,_)' // / ``--...____..-' /// / //  
*  Ascii-Art by Felix Lee <flee@cse.psu.edu>
*
* Freya is free software: you can redistribute it and/or modify
* it under the terms of the GNU General Public License as published by
* the Free Software Foundation, either version 3 of the License, or
* (at your option) any later version.
*
* Freya is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
* GNU General Public License for more details.
*
* You should have received a copy of the GNU General Public License
* along with Freya. If not, see <http://www.gnu.org/licenses/>.
**************************************************************/
#include "SettingsOutputs.hh"
#include "Settings.hh"
#include "../../MPD/AudioOutput.hh"
#include "../../Log/Writer.hh"

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
        treeViewPtr->get_selection()->set_select_function( sigc::mem_fun(*this,&Browser::SettingsOutputs::on_select));
    }

    /* ------------------------------- */

    SettingsOutputs::~SettingsOutputs()
    {
        clear();
    }

    /* ------------------------------- */
    
    void SettingsOutputs::clear(void)
    {
        typedef Gtk::TreeModel::Children type_children;
        type_children children = treeModel->children();
        for(type_children::iterator iter = children.begin();iter != children.end(); ++iter)
        {
            delete (*iter)[treeColumns.colOutput];
        }
        treeModel->clear();
    }
    
    /* ------------------------------- */

    void SettingsOutputs::on_toggle(const Glib::ustring& path)
    {
        sett->settings_changed();
    }

    /* ------------------------------- */

    bool SettingsOutputs::on_select(const Glib::RefPtr<Gtk::TreeModel>& model,const Gtk::TreeModel::Path& path, bool)
    {
        return false;
    }

    /* ------------------------------- */

    void SettingsOutputs::on_client_update(enum mpd_idle event, MPD::NotifyData &data)
    {
        if(!running && (event & (MPD_IDLE_OUTPUT)))
        {
            clear();
            mp_Client->fill_outputs(*this);
        }
    }

    /* ------------------------------- */

    void SettingsOutputs::on_connection_change(bool server_changed, bool is_connected)
    {
        treeViewPtr->set_sensitive(is_connected);
    }

    /* ------------------------------- */

    void SettingsOutputs::decline_new_settings(void)
    {
        reset_settings();
    }

    /* ------------------------------- */

    void SettingsOutputs::accept_new_settings(void)
    {
        running = true;
        typedef Gtk::TreeModel::Children type_children;
        type_children children = treeModel->children();
        for(type_children::iterator iter = children.begin();iter != children.end(); ++iter)
        {
            Gtk::TreeModel::Row row = *iter;
            MPD::AudioOutput * output = row[treeColumns.colOutput];
            bool is_active = row[treeColumns.colActive];
            g_assert(output);

            /* Activate previously not enabled output */
            if(is_active && !output->get_enabled())
                output->enable();
            else 
            /* Deactivate previously enabled output */
            if(!is_active && output->get_enabled())
                output->disable();
        }
        treeModel->clear();
        mp_Client->fill_outputs(*this);

        running = false;
    }

    /* ------------------------------- */

    void SettingsOutputs::reset_settings(void)
    {
        running = true;
        typedef Gtk::TreeModel::Children type_children;
        type_children children = treeModel->children();
        for(type_children::iterator iter = children.begin();iter != children.end(); ++iter)
        {
            Gtk::TreeModel::Row row = *iter;
            row[treeColumns.colActive] = (*(row[treeColumns.colOutput])).get_enabled();
        }
        running = false;
    }

    /* ------------------------------- */

    void SettingsOutputs::add_item(AbstractComposite * item)
    {
        MPD::AudioOutput* a_item = static_cast<MPD::AudioOutput*>(item);
        Gtk::TreeModel::Row row = *(treeModel->append());
        row[treeColumns.colName] = a_item->get_name();
        row[treeColumns.colActive] = a_item->get_enabled();
        row[treeColumns.colOutput] = a_item;
    }
}
