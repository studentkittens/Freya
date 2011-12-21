#include "QueueModelColumns.hh"

namespace Browser
{
    QueueModelColumns::QueueModelColumns()
    { 
        add(m_col_id); 
        add(m_col_pos);
        add(m_col_artist);
        add(m_col_album);
        add(m_col_title); 
    }
}
