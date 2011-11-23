ADD_LIBRARY(FreyaBrowserLib STATIC 
    PlaylistTreeView.cc
    PlaylistManager.cc
    Database.cc
    )

TARGET_LINK_LIBRARIES(FreyaBrowserLib ${GTKMM3_PACKAGE_LIBRARIES})
