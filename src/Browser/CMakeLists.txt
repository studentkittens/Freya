ADD_LIBRARY(FreyaBrowserLib STATIC 
    BasePopup.cc
    Queue.cc
    QueuePopup.cc
    PlaylistManager.cc
    PlaylistManagerPopup.cc
    PlaylistAddDialog.cc
    Database.cc
    DatabasePopup.cc
    StatBrowser.cc
    Settings.cc
    SettingsNetwork.cc
    SettingsGeneral.cc
    SettingsPlayback.cc
    )

TARGET_LINK_LIBRARIES(FreyaBrowserLib FreyaAvahiLib ${GTKMM3_PACKAGE_LIBRARIES})
