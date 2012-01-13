ADD_LIBRARY(FreyaMPDLib 
            Connection.cc
            Listener.cc
            BaseClient.cc
            Client.cc
            Status.cc
            Statistics.cc
            Playlist.cc
            Song.cc
            Directory.cc
            AudioOutput.cc
            NotifyData.cc
            )

TARGET_LINK_LIBRARIES(
    FreyaMPDLib 
    ${GLIBMM_PACKAGE_LIBRARIES}
    ${LIBMPDCLIENT_LIBRARIES}
    FreyaLogHandlerLib 
    FreyaConfigLib
)

# Test cases
IF(CXXTEST_FOUND)
    MESSAGE("Building MPD")
    CXXTEST_ADD_TEST(check_mpd check_mpd.cc ${CMAKE_CURRENT_SOURCE_DIR}/check_mpd.hh)
    TARGET_LINK_LIBRARIES(check_mpd FreyaMPDLib)
ENDIF()

ADD_EXECUTABLE(test_client test_client.cc)
TARGET_LINK_LIBRARIES(test_client FreyaMPDLib)
