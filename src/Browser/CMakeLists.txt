ADD_LIBRARY(FreyaBrowserLib STATIC 
    BasePopup.cc
    Queue/Queue.cc
    Queue/QueueModelColumns.cc
    Queue/QueuePopup.cc
    Queue/QueueMerger.cc
    Queue/PlaylistAddDialog.cc
    PlaylistManager/PlaylistManager.cc
    PlaylistManager/PlaylistManagerPopup.cc
    Database/Database.cc
    Database/DatabasePopup.cc
    Database/DatabaseCache.cc
    Statistics/StatBrowser.cc
    Settings/Settings.cc
    Settings/SettingsNetwork.cc
    Settings/SettingsGeneral.cc
    Settings/SettingsPlayback.cc
    Settings/SettingsOutputs.cc
    Fortuna/Fortuna.cc
    )

TARGET_LINK_LIBRARIES(FreyaBrowserLib FreyaAvahiLib ${GTKMM3_PACKAGE_LIBRARIES})
