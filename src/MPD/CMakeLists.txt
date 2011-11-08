ADD_LIBRARY(FreyaMPDLib MPDConnection.cc MPDConnectionHandler.cc MPDClientHandler.cc IdleListener.cc)
TARGET_LINK_LIBRARIES(
    FreyaMPDLib 
    ${GLIBMM_PACKAGE_LIBRARIES}
    ${LIBMPDCLIENT_LIBRARIES}
    FreyaLogHandlerLib 
    FreyaConfigLib
)

ADD_EXECUTABLE(test_client test_client.cc)
TARGET_LINK_LIBRARIES(test_client FreyaMPDLib)
