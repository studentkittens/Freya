ADD_LIBRARY(FreyaBrowserLib STATIC 
    PlaylistTreeView.cc
    PlaylistManager.cc
    )

TARGET_LINK_LIBRARIES(FreyaBrowserLib ${GTKMM3_PACKAGE_LIBRARIES})
