ADD_LIBRARY(FreyaUtils STATIC Utils.cc CompileSymbols.cc)
TARGET_LINK_LIBRARIES(FreyaUtils FreyaLogHandlerLib ${GTKMM3_PACKAGE_LIBRARIES})
ADD_EXECUTABLE(test_utils test_utils.cc)
TARGET_LINK_LIBRARIES(test_utils FreyaUtils)

# Test cases
IF(CXXTEST_FOUND)
    CXXTEST_ADD_TEST(check_utils check_utils.cc ${CMAKE_CURRENT_SOURCE_DIR}/check_utils.hh)
    TARGET_LINK_LIBRARIES(check_utils FreyaUtils)
ENDIF()

