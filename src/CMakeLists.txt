ADD_SUBDIRECTORY(AvahiBrowser)
ADD_SUBDIRECTORY(Config)
ADD_SUBDIRECTORY(Log)
ADD_SUBDIRECTORY(MPD)

ADD_EXECUTABLE(test_mockup MainWindow.cc PlaylistTreeView.cc PlaybackButtons.cc BrowserList.cc Statusbar.cc Timeslide.cc)
TARGET_LINK_LIBRARIES(test_mockup ${GTKMM3_PACKAGE_LIBRARIES} FreyaMPDLib FreyaConfigLib)
