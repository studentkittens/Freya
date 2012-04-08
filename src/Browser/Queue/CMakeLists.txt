ADD_LIBRARY(FreyaBrowserQueueLib STATIC 
    Queue.cc
    QueueModelColumns.cc
    QueuePopup.cc
    QueueMerger.cc
    PlaylistAddDialog.cc
    )

TARGET_LINK_LIBRARIES(FreyaBrowserQueueLib ${GTKMM3_PACKAGE_LIBRARIES})
