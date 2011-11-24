ADD_LIBRARY(FreyaBrowserLib STATIC 
    PlaylistTreeView.cc
    PlaylistManager.cc
    Database.cc
    StatBrowser.cc
    Settings.cc
    SettingsNetwork.cc
    SettingsGeneral.cc
    SettingsPlayback.cc
    )

TARGET_LINK_LIBRARIES(FreyaBrowserLib FreyaAvahiLib ${GTKMM3_PACKAGE_LIBRARIES})
