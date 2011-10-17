CMAKE_MINIMUM_REQUIRED(VERSION 2.6)
PROJECT(Freya CXX)

# Include pkg-config
INCLUDE(FindPkgConfig)

# ------------------------------------------------
# Versioning 
# ------------------------------------------------
SET(FREYA_VERSION_MAJOR "0")
SET(FREYA_VERSION_MINOR "0")
SET(FREYA_VERSION_MICRO "0")
SET(FREYA_VERSION_NAME  "Terrifying Tarantula") 
# ------------------------------------------------

# ------------------------------------------------
# CFlags and warnlevel / build config 
# ------------------------------------------------

SET(COMMON_FLAGS "-Wall -Wstrict-prototypes -std=c++0x -W -Wno-unused-parameter -Wno-strict-prototypes -ggdb3")
SET(CMAKE_C_FLAGS_RELEASE "${COMMON_FLAGS} ${CMAKE_C_FLAGS} -Os -march=native -s")
SET(CMAKE_C_FLAGS_DEBUG   "${COMMON_FLAGS} ${CMAKE_C_FLAGS} -ggdb3")
SET(CMAKE_C_FLAGS "        ${COMMON_FLAGS} ${CMAKE_C_FLAGS}")
# ------------------------------------------------

# ----------------------
# Find deps
# ----------------------
FIND_PACKAGE(CURL REQUIRED)
PKG_CHECK_MODULES(GLIBPKG glibmm-2.4 REQUIRED)
PKG_CHECK_MODULES(LIBMPDCLIENT libmpdclient REQUIRED)
INCLUDE_DIRECTORIES(${GLIBPKG_INCLUDE_DIRS})

# --------------------------
# set directories
# --------------------------

SET(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/bin CACHE PATH "Single Directory for all Libraries")
SET(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/bin CACHE PATH "Single Directory for all Executables.")

# Add src/CMakeLists.txt
ADD_SUBDIRECTORY(src)
