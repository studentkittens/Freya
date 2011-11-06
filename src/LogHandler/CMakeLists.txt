ADD_LIBRARY(FreyaLogHandlerLib STATIC LogHandler.cc)
TARGET_LINK_LIBRARIES(FreyaLogHandlerLib ${GLIBMM_PACKAGE_LIBRARIES})

ADD_EXECUTABLE(test_log test_log.cc)
TARGET_LINK_LIBRARIES(test_log FreyaLogHandlerLib)
