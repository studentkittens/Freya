ADD_LIBRARY(FreyaBrowserLib STATIC 
    BasePopup.cc
    Queue.cc
    QueueModelColumns.cc
    QueuePopup.cc
    QueueMerger.cc
    PlaylistManager.cc
    PlaylistManagerPopup.cc
    PlaylistAddDialog.cc
    Database.cc
    DatabasePopup.cc
    DatabaseCache.cc
    StatBrowser.cc
    Settings.cc
    SettingsNetwork.cc
    SettingsGeneral.cc
    SettingsPlayback.cc
    Fortuna.cc
    )

TARGET_LINK_LIBRARIES(FreyaBrowserLib FreyaAvahiLib ${GTKMM3_PACKAGE_LIBRARIES})
