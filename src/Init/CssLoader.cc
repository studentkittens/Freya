#include <gtkmm/cssprovider.h>
#include <gtkmm/stylecontext.h>

#include "Path.hh"
#include "defaultcss.inl"
#include "CssLoader.hh"

#include "../Log/Writer.hh"

namespace Init 
{
    CssLoader::CssLoader()
    {
        Init::Path cfg;
        bool load_from_data = false;
        Glib::ustring cssPath = cfg.get_config_dir() + "/style.css";

        Glib::RefPtr<Gtk::CssProvider> cssProv = Gtk::CssProvider::create();
        Glib::RefPtr<Gtk::StyleContext> ctx = Gtk::StyleContext::create();

        try {
            cssProv->load_from_path(cssPath);
        } catch(...) {
            load_from_data = true;

            FILE * overlay = fopen(cssPath.c_str(),"w");
            if(overlay != NULL) {
                Info("Wrote default css-style to %s",cssPath.c_str());
                fprintf(overlay,Init::defaultcss_inl.c_str());
                fclose(overlay);
            } else {
                Warning("No css-style loaded from %s",cssPath.c_str());
            }
        }

        if(load_from_data) {
            cssProv->load_from_data(Init::defaultcss_inl);
        }

        ctx->add_provider_for_screen(Gdk::Screen::get_default(),cssProv,INT_MAX);
    }
}
