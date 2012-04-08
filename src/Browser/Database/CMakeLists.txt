ADD_LIBRARY(FreyaBrowserDatabaseLib STATIC
    Database.cc
    DatabasePopup.cc
    DatabaseCache.cc
    )

TARGET_LINK_LIBRARIES(FreyaBrowserDatabaseLib ${GTKMM3_PACKAGE_LIBRARIES})
