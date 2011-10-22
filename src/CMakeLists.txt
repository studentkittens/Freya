ADD_EXECUTABLE(mpd_shell mpd_shell.cc)
TARGET_LINK_LIBRARIES(mpd_shell ${GLIBPKG_LIBRARIES} ${LIBMPDCLIENT_LIBRARIES})

ADD_EXECUTABLE(client 
           MPDConnection.cc
           MPDConnectionHandler.cc 
           MPDClientHandler.cc
           IdleListener.cc
           main.cc 
           )

TARGET_LINK_LIBRARIES(client ${GLIBPKG_LIBRARIES} ${LIBMPDCLIENT_LIBRARIES})
