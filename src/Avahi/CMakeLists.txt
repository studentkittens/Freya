# Check for Avahi
PKG_CHECK_MODULES(AVAHI_PACKAGE avahi-glib avahi-client REQUIRED)
INCLUDE_DIRECTORIES(${AVAHI_PACKAGE_INCLUDE_DIRS})

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
