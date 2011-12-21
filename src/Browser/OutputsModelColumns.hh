#ifndef FREYA_OUTPUTCOLUMNS_GUARD
#define FREYA_OUTPUTCOLUMNS_GUARD

namespace Browser
{
    class OutputsModelColumns : public Gtk::TreeModel::ColumnRecord
    {
        public:
            OutputsModelColumns()
            { add(colName); add(colActive);}
            Gtk::TreeModelColumn<Glib::ustring> colName;
            Gtk::TreeModelColumn<bool> colActive;
    };
                                                                                                            
}

#endif