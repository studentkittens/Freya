if(USE_LIBNOTIFY)
    ADD_LIBRARY(FreyaNotifyLib STATIC Notify.cc)
    TARGET_LINK_LIBRARIES(FreyaNotifyLib ${LIBNOTIFY_PACKAGE_LIBRARIES} ${GLIBMM_PACKAGE_LIBRARIES} FreyaLogHandlerLib)

    # Test cases
    IF(CXXTEST_FOUND)
        CXXTEST_ADD_TEST(check_notify check_nofity.cc ${CMAKE_CURRENT_SOURCE_DIR}/check_notify.hh)
        TARGET_LINK_LIBRARIES(check_notify FreyaNotifyLib)
    ENDIF()
endif()
