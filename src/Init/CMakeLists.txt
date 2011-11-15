ADD_LIBRARY(FreyaInit STATIC Initpath.cc)
TARGET_LINK_LIBRARIES(FreyaInit
                     ${GLIBMM_PACKAGE_LIBRARIES}
                     FreyaLogHandlerLib
                     FreyaConfigLib
)
ADD_EXECUTABLE(test_path test_path.cc)
TARGET_LINK_LIBRARIES(test_path FreyaInit)
