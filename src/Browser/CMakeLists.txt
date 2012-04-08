ADD_SUBDIRECTORY(Avahi)
ADD_SUBDIRECTORY(NowPlaying)

# required
ADD_SUBDIRECTORY(Database)
ADD_SUBDIRECTORY(Fortuna)
ADD_SUBDIRECTORY(PlaylistManager)
ADD_SUBDIRECTORY(Queue)
ADD_SUBDIRECTORY(Settings)
ADD_SUBDIRECTORY(Statistics)

ADD_LIBRARY(FreyaBrowserLib STATIC BasePopup.cc)

if(USE_GLYR)
    SET(OptionalBrowserDeps ${OptionalBrowserDeps} FreyaNowPlayingLib)
endif()

if(USE_AVAHI)
    SET(OptionalBrowserDeps ${OptionalBrowserDeps} FreyaServerListLib)
endif()

TARGET_LINK_LIBRARIES(FreyaBrowserLib 
    FreyaUtils 
    FreyaBrowserDatabaseLib
    FreyaBrowserFortunaLib
    FreyaBrowserPlaylistLib
    FreyaBrowserQueueLib
    FreyaBrowserSettingsLib
    FreyaBrowserStatisticsLib
    ${OptionalBrowserDeps}
    ${GTKMM3_PACKAGE_LIBRARIES}
    )
