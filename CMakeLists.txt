CMAKE_MINIMUM_REQUIRED(VERSION 2.6)
PROJECT(Freya CXX)

# Include pkg-config
INCLUDE(FindPkgConfig)
INCLUDE(CheckCXXCompilerFlag)

# ------------------------------------------------
# Feature Set 
# ------------------------------------------------
if(NOT DEFINED USE_GLYR)
    SET(USE_GLYR  true)
endif() 

if(NOT DEFINED USE_AVAHI)
    SET(USE_AVAHI true)
endif()

if(NOT DEFINED USE_LIBNOTIFY)
    SET(USE_LIBNOTIFY true)
endif()

# ------------------------------------------------
# Versioning 
# ------------------------------------------------
SET(FREYA_VERSION_MAJOR "0")
SET(FREYA_VERSION_MINOR "0")
SET(FREYA_VERSION_MICRO "1")
SET(FREYA_VERSION_NAME  "Compiling Cat") 
# ------------------------------------------------

IF(NOT DEFINED INSTALL_BIN_DIR)
 SET(INSTALL_BIN_DIR bin)
ELSE()
  MESSAGE("-- Install binaries to: \"${INSTALL_BIN_DIR}\"")
ENDIF()

# ------------------------------------------------
# CFlags and warnlevel / build config 
# ------------------------------------------------
SET(COMMON_FLAGS "-Wall -Wextra -std=c++0x -Wno-unused-parameter -pipe")
SET(CMAKE_CXX_FLAGS_RELEASE "${COMMON_FLAGS} ${CMAKE_CXX_FLAGS} -Os -s -march=native")
SET(CMAKE_CXX_FLAGS_DEBUG   "${COMMON_FLAGS} ${CMAKE_CXX_FLAGS} -ggdb3")
SET(CMAKE_CXX_FLAGS         "${COMMON_FLAGS} ${CMAKE_CXX_FLAGS}")
ADD_DEFINITIONS(${CMAKE_CXX_FLAGS})
# ------------------------------------------------

IF(CMAKE_BUILD_TYPE STREQUAL "debug")
    SET(FREYA_DEBUG true)
ELSE()
    SET(CMAKE_BUILD_TYPE "release")
    SET(FREYA_DEBUG false)
ENDIF()
MESSAGE("-- Building Target: ${CMAKE_BUILD_TYPE}")

# ----------------------
# Find required deps
# ----------------------
PKG_CHECK_MODULES(GTKMM3_PACKAGE REQUIRED gtkmm-3.0)
PKG_CHECK_MODULES(GLIBMM_PACKAGE REQUIRED glibmm-2.4)
PKG_CHECK_MODULES(LIBMPDCLIENT REQUIRED libmpdclient)
PKG_CHECK_MODULES(LIBXML2_PACKAGE REQUIRED libxml-2.0)

# Optional Feature: Notifcations 
PKG_CHECK_MODULES(LIBNOTIFY_PACKAGE OPTIONAL libnotify)
if(NOT LIBNOTIFY_PACKAGE_FOUND)
    MESSAGE("Disabling libnotify support, since deps were not found.")
    SET(USE_LIBNOTIFY false)
else()
    INCLUDE_DIRECTORIES(${LIBNOTIFY_PACKAGE_INCLUDE_DIRS})
endif()

# Optional Feature: NowPlaying browser
PKG_CHECK_MODULES(LIBGLYR_PACKAGE libglyr)
if(NOT LIBGLYR_PACKAGE_FOUND)
    MESSAGE("Disabling glyr support, since deps were not found.")
    SET(USE_GLYR false)
else()
    INCLUDE_DIRECTORIES(${LIBGLYR_PACKAGE_INCLUDE_DIRS})
endif()

# Optional Feature: Avahi Serverlist
PKG_CHECK_MODULES(AVAHI_PACKAGE avahi-glib avahi-client)
if(NOT AVAHI_PACKAGE_FOUND)
    MESSAGE("Disabling avahi support, since deps were not found.")
    SET(USE_AVAHI false)
else()
    INCLUDE_DIRECTORIES(${AVAHI_PACKAGE_INCLUDE_DIRS})
endif()

INCLUDE_DIRECTORIES(${GTKMM3_PACKAGE_INCLUDE_DIRS})
INCLUDE_DIRECTORIES(${GLIBMM_PACKAGE_INCLUDE_DIRS})
INCLUDE_DIRECTORIES(${LIBMPDCLIENT_PACKAGE_INCLUDE_DIRS})
INCLUDE_DIRECTORIES(${LIBXML2_PACKAGE_INCLUDE_DIRS})

# --------------------------
# set directories
# --------------------------
SET(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/bin CACHE PATH "Single Directory for all Libraries")
SET(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/bin CACHE PATH "Single Directory for all Executables")

# --------------------------
# config.h generation 
# --------------------------
configure_file (
    "config.h.in"
    "config.h"
    )

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

ADD_CUSTOM_TARGET(tex 
    COMMAND cd ${PROJECT_SOURCE_DIR}/doc/architecture && pdflatex -output-directory out/ doku.tex 
    COMMENT "Generate Latex documents" VERBATIM
    )

# --------------------------
# Add src/CMakeLists.txt
# --------------------------
ADD_SUBDIRECTORY(src)


# --------------------------
# uninstall target
# --------------------------
configure_file(
    "${CMAKE_CURRENT_SOURCE_DIR}/cmake_uninstall.cmake.in"
    "${CMAKE_CURRENT_BINARY_DIR}/cmake_uninstall.cmake"
    IMMEDIATE @ONLY
    )

ADD_CUSTOM_TARGET(uninstall COMMAND ${CMAKE_COMMAND} -P ${CMAKE_CURRENT_BINARY_DIR}/cmake_uninstall.cmake)

# --------------------------
# dest target
# --------------------------

ADD_CUSTOM_TARGET(release COMMAND "ruby" "scripts/amalgamation.rb > ${CMAKE_CURRENT_SOURCE_DIR}/src/Utils/CompileSymbols.cc")

# --------------------------
# dest target
# --------------------------
SET(ARCHIVE_NAME ${CMAKE_PROJECT_NAME}-${PROJECT_VERSION})
ADD_CUSTOM_TARGET(dist
    COMMAND git archive --prefix=${CMAKE_PROJECT_NAME}/ HEAD
    | bzip2 > ${CMAKE_BINARY_DIR}/${ARCHIVE_NAME}.tar.bz2
    WORKING_DIRECTORY ${CMAKE_SOURCE_DIR})

# --------------------------
# Output Feature set 
# --------------------------
MESSAGE("-- Will compile following feature set:                                         ")
MESSAGE("                                                                               ")
MESSAGE("      * (-DUSE_GLYR)      Use libglyr (Now Playing Browser):  ${USE_GLYR}      ")
MESSAGE("      * (-DUSE_LIBNOTIFY) Use libnotify (For notifcations) :  ${USE_LIBNOTIFY} ")
MESSAGE("      * (-DUSE_AVAHI)     Use Avahi (Built-in Serverlist)  :  ${USE_AVAHI}     ")
MESSAGE("                                                                               ")

ADD_SUBDIRECTORY(data)

