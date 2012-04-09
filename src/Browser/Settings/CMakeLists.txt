ADD_LIBRARY(FreyaBrowserSettingsLib STATIC 
    Settings.cc
    SettingsNetwork.cc
    SettingsGeneral.cc
    SettingsPlayback.cc
    SettingsOutputs.cc
    )
TARGET_LINK_LIBRARIES(FreyaBrowserSettingsLib ${GTKMM3_PACKAGE_LIBRARIES})
