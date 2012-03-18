#include "TextItemsMgr.hh"
#include "TextPageMgr.hh"
#include "../../Utils/Utils.hh"

namespace Browser
{
    TextItemsMgr::TextItemsMgr(BaseObjectType* cobject, const Glib::RefPtr<Gtk::Builder>& builder)
        : Gtk::Expander(cobject)
    {
        BUILDER_GET(builder,"np_notebook",mp_NBook);

        /* 
         * Type selector (lyrics, album review etc.)
         * Connect signals, and setup internal model
         */
        BUILDER_GET(builder,"np_TypeCombo", mp_TypeSelection);

        /* Setup combobox */
        {
            m_TypeModel = Gtk::ListStore::create(m_TypeColumns); 
            mp_TypeSelection->set_model(m_TypeModel);       

            /* Clear all previous renderers */
            mp_TypeSelection->clear();

            /* Add custom renderer for the icon */
            Gtk::CellRenderer * renderer = NULL;

            renderer = manage (new Gtk::CellRendererPixbuf); 
            mp_TypeSelection->pack_start(*renderer,false);
            mp_TypeSelection->add_attribute(*renderer,"pixbuf",1);

            renderer = manage (new Gtk::CellRendererText); 
            mp_TypeSelection->pack_start(*renderer,true);
            mp_TypeSelection->add_attribute(*renderer,"text",0);

            /* 
             * Connect the selection signal to the 
             * changing of the Notebook page
             */ 
            mp_TypeSelection->signal_changed().connect(sigc::mem_fun(*this,
                        &TextItemsMgr::on_type_combo_changed));
        }

        add_txtview_page(builder,GLYR_GET_LYRICS,"Songtext",Gtk::Stock::FILE);
        add_txtview_page(builder,GLYR_GET_ARTISTBIO,"Artist Biography",Gtk::Stock::ORIENTATION_PORTRAIT);
        add_txtview_page(builder,GLYR_GET_ALBUM_REVIEW,"Album Review",Gtk::Stock::CDROM);
        mp_TypeSelection->set_active(0);
    }

    /////////////////////////////
    ///////// Private ///////////
    /////////////////////////////

    void TextItemsMgr::add_txtview_page(const Glib::RefPtr<Gtk::Builder>& builder, GLYR_GET_TYPE type, const char * name, Gtk::StockID icon)
    {
        Glib::RefPtr<Gtk::Builder> temp_builder = Gtk::Builder::create();
        BUILDER_ADD(temp_builder,"ui/NowPlaying_TextView.glade");
        if(temp_builder) 
        {
            TextPageMgr * pageMgr;
            ADD_MANAGER(temp_builder,"np_textview_scw",pageMgr);

            if(pageMgr != NULL) {
                pageMgr->set_request_type(type);
                Gtk::TreeModel::Row row = *(m_TypeModel->append());
                row[m_TypeColumns.m_col_id]   = name; 
                row[m_TypeColumns.m_col_icon] = mp_NBook->render_icon_pixbuf(icon,Gtk::ICON_SIZE_DND);
                mp_NBook->append_page(*pageMgr,name);
            }
        }
        else
        {
            Error("Cannot instantiate temporate builder");
            Error("Does NowPlaying_TextView.glade exist?");
        }
    }

    /////////////////////////////

    /* 
     * When selecting a type in the Combobox, jump to 
     * the specified field in the notebook
     */ 
    void TextItemsMgr::on_type_combo_changed()
    {
        mp_NBook->set_current_page(mp_TypeSelection->get_active_row_number()); 
    }
    
    /////////////////////////////////

    void TextItemsMgr::update(MPD::Client& client, mpd_idle events, MPD::NotifyData& data)
    {
        managerList.at(mp_TypeSelection->get_active_row_number())->update(client,events,data);
    }
}
