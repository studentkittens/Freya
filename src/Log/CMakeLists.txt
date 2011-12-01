ADD_LIBRARY(FreyaLogHandlerLib STATIC Writer.cc)
TARGET_LINK_LIBRARIES(FreyaLogHandlerLib ${GLIBMM_PACKAGE_LIBRARIES} FreyaInit)

# Direct access utility
ADD_EXECUTABLE(test_log test_log.cc)
TARGET_LINK_LIBRARIES(test_log FreyaLogHandlerLib)

# Test cases
IF(CXXTEST_FOUND)
    MESSAGE("Building Log")
    CXXTEST_ADD_TEST(check_log check_log.cc ${CMAKE_CURRENT_SOURCE_DIR}/check_log.hh)
    TARGET_LINK_LIBRARIES(check_log FreyaLogHandlerLib)
ENDIF()
