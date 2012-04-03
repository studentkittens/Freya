if(USE_LIBNOTIFY)
    ADD_LIBRARY(FreyaGManagerNotifyLib STATIC NotifyManager.cc)
    TARGET_LINK_LIBRARIES(FreyaGManagerNotifyLib FreyaNotifyLib)
endif()

ADD_LIBRARY(FreyaGManagerLib STATIC 
    Window.cc
    PlaybackButtons.cc
    BrowserList.cc
    Statusbar.cc
    Timeslide.cc
    TitleLabel.cc
    StatusIcons.cc
    VolumeSlider.cc
    Heartbeat.cc
    Trayicon.cc
    MenuList.cc
    CairoSlider.cc
    )

if(USE_LIBNOTIFY)
    SET(OptionalGManagerFeatures ${OptionalGManagerFeatures} FreyaGManagerNotifyLib)
endif()
    
TARGET_LINK_LIBRARIES(FreyaGManagerLib ${GTKMM3_PACKAGE_LIBRARIES} ${OptionalGManagerFeatures} FreyaMPDLib FreyaConfigLib)
