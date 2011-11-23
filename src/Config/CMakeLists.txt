ADD_LIBRARY(FreyaConfigLib STATIC Handler.cc Model.cc)
TARGET_LINK_LIBRARIES(FreyaConfigLib
                     ${GLIBMM_PACKAGE_LIBRARIES}
                     ${LIBXML2_PACKAGE_LIBRARIES}
                     FreyaLogHandlerLib
                     FreyaInit
)
ADD_EXECUTABLE(test_config test_config.cc)
TARGET_LINK_LIBRARIES(test_config FreyaConfigLib)
