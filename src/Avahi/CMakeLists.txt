IF(USE_AVAHI)
    ADD_LIBRARY(FreyaAvahiLib STATIC Browser.cc)
    TARGET_LINK_LIBRARIES(FreyaAvahiLib 
        ${GLIBMM_PACKAGE_LIBRARIES}
        ${AVAHI_PACKAGE_LIBRARIES}
        FreyaLogHandlerLib
        FreyaConfigLib
        FreyaUtils
        )

    ADD_EXECUTABLE(test_avahi test_avahi.cc)
    TARGET_LINK_LIBRARIES(test_avahi FreyaAvahiLib)
ENDIF(USE_AVAHI)
