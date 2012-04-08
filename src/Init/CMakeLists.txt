ADD_LIBRARY(FreyaInit STATIC Path.cc SignalHandler.cc CssLoader.cc cmdoptions.cc)
TARGET_LINK_LIBRARIES(FreyaInit ${GTKMM3_PACKAGE_LIBRARIES})
ADD_EXECUTABLE(test_path test_path.cc)
TARGET_LINK_LIBRARIES(test_path FreyaInit)
