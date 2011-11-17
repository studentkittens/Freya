ADD_LIBRARY(FreyaGManagerLib STATIC 
    PlaylistTreeView.cc
    PlaybackButtons.cc
    BrowserList.cc
    Statusbar.cc
    Timeslide.cc
    TitleLabel.cc
    StatusIcons.cc
    Volumebutton.cc
    )

TARGET_LINK_LIBRARIES(FreyaGManagerLib ${GTKMM3_PACKAGE_LIBRARIES} FreyaMPDLib FreyaConfigLib)
