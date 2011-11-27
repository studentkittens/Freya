ADD_LIBRARY(FreyaGManagerLib STATIC 
    PlaybackButtons.cc
    BrowserList.cc
    Statusbar.cc
    Timeslide.cc
    TitleLabel.cc
    StatusIcons.cc
    Volumebutton.cc
    Heartbeat.cc
    MenuList.cc
    )

TARGET_LINK_LIBRARIES(FreyaGManagerLib ${GTKMM3_PACKAGE_LIBRARIES} FreyaMPDLib FreyaConfigLib)
