#ifndef FREYA_OUTPUTCOLUMNS_GUARD
#define FREYA_OUTPUTCOLUMNS_GUARD
#include "../MPD/AudioOutput.hh"
namespace Browser
{
    class OutputsModelColumns : public Gtk::TreeModel::ColumnRecord
    {
        public:
            OutputsModelColumns()
            { add(colName); add(colActive); add(colOutput);}
            Gtk::TreeModelColumn<Glib::ustring> colName;
            Gtk::TreeModelColumn<bool> colActive;
            Gtk::TreeModelColumn<MPD::AudioOutput*> colOutput;
    };
                                                                                                            
}

#endif