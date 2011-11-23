ADD_LIBRARY(FreyaMPDLib 
            Connection.cc
            Client.cc
            Listener.cc
            Status.cc
            Statistics.cc
            Playlist.cc
            Song.cc
            NotifyData.cc
            )

TARGET_LINK_LIBRARIES(
    FreyaMPDLib 
    ${GLIBMM_PACKAGE_LIBRARIES}
    ${LIBMPDCLIENT_LIBRARIES}
    FreyaLogHandlerLib 
    FreyaConfigLib
)

ADD_EXECUTABLE(test_client test_client.cc)
TARGET_LINK_LIBRARIES(test_client FreyaMPDLib)
