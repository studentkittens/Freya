ADD_LIBRARY(FreyaInit STATIC Path.cc SignalHandler.cc)
TARGET_LINK_LIBRARIES(FreyaInit
                     ${GLIBMM_PACKAGE_LIBRARIES}
)
ADD_EXECUTABLE(test_path test_path.cc)
TARGET_LINK_LIBRARIES(test_path FreyaInit)
