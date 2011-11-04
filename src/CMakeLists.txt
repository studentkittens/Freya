ADD_EXECUTABLE(Freya MainWindow.cc)
TARGET_LINK_LIBRARIES(Freya ${GTKMM3_PACKAGE_LIBRARIES})

ADD_EXECUTABLE(client 
               MPDConnection.cc
               MPDConnectionHandler.cc 
               MPDClientHandler.cc
               IdleListener.cc
               main.cc)

TARGET_LINK_LIBRARIES(client ${GTKMM3_PACKAGE_LIBRARIES} ${LIBMPDCLIENT_LIBRARIES})
