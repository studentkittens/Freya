CMAKE_MINIMUM_REQUIRED(VERSION 2.6)
PROJECT(Freya CXX)

# Include pkg-config
INCLUDE(FindPkgConfig)
INCLUDE(CheckCXXCompilerFlag)
# some comment

# ------------------------------------------------
# Versioning 
# ------------------------------------------------
SET(FREYA_VERSION_MAJOR "0")
SET(FREYA_VERSION_MINOR "0")
SET(FREYA_VERSION_MICRO "0")
SET(FREYA_VERSION_NAME  "Terrifying Tarantula") 
# ------------------------------------------------

# a new comment

# ------------------------------------------------
# CFlags and warnlevel / build config 
# ------------------------------------------------
SET(COMMON_FLAGS "-Wall -Wextra -std=c++0x -Wno-unused-parameter -ggdb3 -pipe")
SET(CMAKE_CXX_FLAGS_RELEASE "${COMMON_FLAGS} ${CMAKE_CXX_FLAGS} -Os -march=native -s")
SET(CMAKE_CXX_FLAGS_DEBUG   "${COMMON_FLAGS} ${CMAKE_CXX_FLAGS} -ggdb3")
SET(CMAKE_CXX_FLAGS         "${COMMON_FLAGS} ${CMAKE_CXX_FLAGS}")
ADD_DEFINITIONS(${CMAKE_CXX_FLAGS})
# ------------------------------------------------

# ----------------------
# Find required deps
# ----------------------
PKG_CHECK_MODULES(GTKMM3_PACKAGE gtkmm-3.0 REQUIRED)
PKG_CHECK_MODULES(GLIBMM_PACKAGE glibmm-2.4 REQUIRED)
PKG_CHECK_MODULES(LIBMPDCLIENT libmpdclient REQUIRED)
PKG_CHECK_MODULES(LIBXML2_PACKAGE libxml-2.0 REQUIRED)
PKG_CHECK_MODULES(LIBNOTIFY_PACKAGE libnotify REQUIRED)
INCLUDE_DIRECTORIES(${GTKMM3_PACKAGE_INCLUDE_DIRS})
INCLUDE_DIRECTORIES(${GLIBMM_PACKAGE_INCLUDE_DIRS})
INCLUDE_DIRECTORIES(${LIBMPDCLIENT_PACKAGE_INCLUDE_DIRS})
INCLUDE_DIRECTORIES(${LIBXML2_PACKAGE_INCLUDE_DIRS})
INCLUDE_DIRECTORIES(${LIBNOTIFY_PACKAGE_INCLUDE_DIRS})

# --------------------------
# set directories
# --------------------------
SET(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/bin CACHE PATH "Single Directory for all Libraries")
SET(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/bin CACHE PATH "Single Directory for all Executables.")

# --------------------------
# cxxtest - Tip from: http://battlemidget.blogspot.com/2010/03/c-cxxtest-cmake.html
# --------------------------
FIND_PACKAGE(CxxTest)
IF(CXXTEST_FOUND)
    FIND_PACKAGE(Perl QUIET)
    INCLUDE_DIRECTORIES(${CXXTEST_INCLUDE_DIR})
    ENABLE_TESTING()
ENDIF()

ADD_CUSTOM_TARGET(doc 
    COMMAND doxygen ${PROJECT_SOURCE_DIR}/FreyaDoxygen.conf
    COMMENT "Generate Doxygen doc" VERBATIM
    )

# --------------------------
# Add src/CMakeLists.txt
# --------------------------
ADD_SUBDIRECTORY(src)
